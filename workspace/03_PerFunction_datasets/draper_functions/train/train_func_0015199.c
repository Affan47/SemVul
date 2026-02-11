setParticleDensity(int tag,int mask,double rho)
{
  CMPILCmdBuffer cmd_buffer(m_global_comm,m_global_rank);
  CVarMPIBuffer buffer(m_global_comm);
  CMPIBarrier barrier(m_global_comm);

  cmd_buffer.broadcast(CMD_PDENS);
  buffer.append(tag);
  buffer.append(mask);
  buffer.append(rho) ;
  buffer.broadcast(m_global_rank);
  barrier.wait("setParticleDensity");
}
