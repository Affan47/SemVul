loadFromFile(const dmtcp::string& path,
                                         dmtcp::SerializedWorkerInfo *info)
{
  int fd = openDmtcpCheckpointFile(path);
  JASSERT(fd != -1);
  jalib::JBinarySerializeReaderRaw rdr(path, fd);
  rdr & info->compGroup;
  rdr & info->numPeers;
  rdr & info->argvSize;
  rdr & info->envSize;
  serialize(rdr);
#ifdef PID_VIRTUALIZATION
  info->virtualPidTable.serialize(rdr);
#endif
  close_ckpt_to_read(fd);
  return rdr.bytes() + strlen(DMTCP_FILE_HEADER);
}
