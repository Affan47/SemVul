packet(uint32 seq, uint8 flags,
                                                uint32 offset, uint32 len) {
  ASSERT(HEADER_SIZE + len <= MAX_PACKET);

  uint32 now = Now();

  uint8 buffer[MAX_PACKET];
  long_to_bytes(m_conv, buffer);
  long_to_bytes(seq, buffer + 4);
  long_to_bytes(m_rcv_nxt, buffer + 8);
  buffer[12] = 0;
  buffer[13] = flags;
  short_to_bytes(static_cast<uint16>(m_rcv_wnd >> m_rwnd_scale), buffer + 14);


  long_to_bytes(now, buffer + 16);
  long_to_bytes(m_ts_recent, buffer + 20);
  m_ts_lastack = m_rcv_nxt;

  if (len) {
    size_t bytes_read = 0;
    talk_base::StreamResult result = m_sbuf.ReadOffset(buffer + HEADER_SIZE,
                                                       len,
                                                       offset,
                                                       &bytes_read);
    UNUSED(result);
    ASSERT(result == talk_base::SR_SUCCESS);
    ASSERT(static_cast<uint32>(bytes_read) == len);
  }

#if _DEBUGMSG >= _DBG_VERBOSE
  LOG(LS_INFO) << "<-- <CONV=" << m_conv
               << "><FLG=" << static_cast<unsigned>(flags)
               << "><SEQ=" << seq << ":" << seq + len
               << "><ACK=" << m_rcv_nxt
               << "><WND=" << m_rcv_wnd
               << "><TS="  << (now % 10000)
               << "><TSR=" << (m_ts_recent % 10000)
               << "><LEN=" << len << ">";
#endif

  IPseudoTcpNotify::WriteResult wres = m_notify->TcpWritePacket(this, reinterpret_cast<char *>(buffer), len + HEADER_SIZE);


  if ((wres != IPseudoTcpNotify::WR_SUCCESS) && (0 != len))
    return wres;

  m_t_ack = 0;
  if (len > 0) {
    m_lastsend = now;
  }
  m_lasttraffic = now;
  m_bOutgoing = true;

  return IPseudoTcpNotify::WR_SUCCESS;
}
