//*****************************************************************
/*
  JackTrip: A System for High-Quality Audio Network Performance
  over the Internet

  Copyright (c) 2008 Juan-Pablo Caceres, Chris Chafe.
  SoundWIRE group at CCRMA, Stanford University.
  
  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation
  files (the "Software"), to deal in the Software without
  restriction, including without limitation the rights to use,
  copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following
  conditions:
  
  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.
*/
//*****************************************************************

/**
 * \file UdpDataProtocol.h
 * \author Juan-Pablo Caceres
 * \date June 2008
 */

#ifndef __UDPDATAPROTOCOL_H__
#define __UDPDATAPROTOCOL_H__

#include <QThread>
#include <QUdpSocket>
#include <QHostAddress>

#include "DataProtocol.h"
#include "types.h"


/** \brief UDP implementation of DataProtocol class
 */
class UdpDataProtocol : public DataProtocol
{
public:

  /** \brief The class constructor 
   * \param runmode Sets the run mode, use either SENDER or RECEIVER
   */
  UdpDataProtocol(JackTrip* jacktrip, const runModeT runmode);
  
  /** \brief The class constructor 
   * \param runmode Sets the run mode, use either SENDER or RECEIVER
   * \param peerHostOrIP IPv4 number or host name
   */
  //UdpDataProtocol(const runModeT runmode, const char* peerHostOrIP);

  /** \brief The class destructor
   */
  virtual ~UdpDataProtocol() {};  


  void setPeerAddress(char* peerHostOrIP);

  /** \brief Receives a packet. It blocks until a packet is received
   *
   * This function makes sure we recieve a complete packet
   * of size n
   * \param buf Buffer to store the recieved packet
   * \param n size of packet to receive
   * \return number of bytes read, -1 on error
   */
  virtual int receivePacket(char* buf, const size_t n);
  
  /** \brief Sends a packet
   *
   * This function meakes sure we send a complete packet
   * of size n
   * \param buff Buffer to send
   * \param n size of packet to receive
   * \return number of bytes read, -1 on error
   */
  virtual int sendPacket(const char* buf, const size_t n);
  
  virtual void getPeerAddressFromFirstPacket(QHostAddress& peerHostAddress,
					     uint16_t& port);

  virtual void run();


private:

  /** \brief Binds the UDP socket to the available address and specified port
   */
  void bindSocket();

  int mLocalPort; ///< Local Port number to Bind
  int mPeerPort; ///< Peer Port number to Bind
  const runModeT mRunMode; ///< Run mode, either SENDER or RECEIVER

  //void setBindSocket();

  QUdpSocket mUdpSocket; ///< The UDP socket
  QHostAddress mPeerAddress; ///< The Peer Address


  /// \todo change this names and location
  int8_t* audio_packet;
  int8_t* full_packet;


};

#endif
