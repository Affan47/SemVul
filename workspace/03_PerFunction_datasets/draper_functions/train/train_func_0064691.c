ReadMessage()
{
  bool bClosed = false;
  MsgPacket* p = MsgPacket::read(m_fd, bClosed, m_timeout);

  if(bClosed)
    SignalConnectionLost();

  return p;
}
