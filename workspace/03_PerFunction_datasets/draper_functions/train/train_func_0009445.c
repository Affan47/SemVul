addShortBondedIG(int tag,const string& name,double k,double break_dist)
{
  CMPILCmdBuffer cmd_buffer(m_global_comm,m_global_rank);
  CVarMPIBuffer pbuffer(m_global_comm,20);
  CMPIBarrier barrier(m_global_comm);

  console.XDebug() << "CLatticeMaster::addShortBondedIG()\n ";


  cmd_buffer.broadcast(CMD_ADDSHORTBONDEDIG);

  pbuffer.append(tag);
  pbuffer.append(name.c_str());
  pbuffer.append(k);
  pbuffer.append(break_dist);

  pbuffer.broadcast(0);


  barrier.wait("addShortBondedIG()");
  console.XDebug() << "end CLatticeMaster::addShortBondedIG()" << "\n";
}
