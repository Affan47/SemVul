SetRecordingPlayCount(const std::string& recid, int count)
{
  MutexLock lock(&m_cmdlock);

  MsgPacket vrp(XVDR_RECORDINGS_SETPLAYCOUNT);
  vrp.put_String(recid.c_str());
  vrp.put_U32(count);

  MsgPacket* vresp = ReadResult(&vrp);
  if (vresp == NULL)
  {
    delete vresp;
    return false;
  }

  delete vresp;
  return true;
}
