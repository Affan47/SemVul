addExIG(const string& s1,const string& s2)
{
  console.XDebug()<<"CLatticeMaster::addExIG\n";

  CVarMPIBuffer pbuffer(m_global_comm,20);
  CMPIBarrier barrier(m_global_comm);
  CMPILCmdBuffer cmd_buffer(m_global_comm,m_global_rank);


  cmd_buffer.broadcast(CMD_EXIG);
  pbuffer.append(s1.c_str());
  pbuffer.append(s2.c_str());
  pbuffer.broadcast(0);
  barrier.wait("addExIG()");
  console.XDebug()<<"end CLatticeMaster::addExIG\n";

  updateInteractions();
}
