addBondedIG(const CBondedIGP &prms)
{
  CMPILCmdBuffer cmd_buffer(m_global_comm,m_global_rank);
  CVarMPIBuffer pbuffer(m_global_comm,20);
  CMPIBarrier barrier(m_global_comm);

  console.XDebug() << "CLatticeMaster::addBondedIG()\n ";


  cmd_buffer.broadcast(CMD_ADDBONDEDIG);

  pbuffer.append(prms.tag);
  pbuffer.append(prms.getName().c_str());
  pbuffer.append(prms.k);
  pbuffer.append(prms.rbreak);
  pbuffer.append(static_cast<int>(prms.m_scaling));

  pbuffer.broadcast(0);

  barrier.wait("addBondedIG()");
  console.XDebug() << "end CLatticeMaster::addBondedIG()" << "\n";
}
