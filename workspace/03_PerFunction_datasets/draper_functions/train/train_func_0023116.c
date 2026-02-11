addTaggedScalarParticleDistributionSaver(const string& filename,const string& fieldname,const string& savetype,int t_0,int t_end,int dt,int t_snap,int tag,int mask,double x_0,double x_max,int nx)
{
  console.Debug() << "CLatticeMaster::addTaggedScalarParticleDistributionSaver(" << filename << ","<< fieldname << "," << t_0 << "," << t_end << "," << dt << ")\n";

  CMPILCmdBuffer cmd_buffer(m_global_comm,m_global_rank);
  CMPIBarrier barrier(m_global_comm);


  cmd_buffer.broadcast(CMD_ADD_SPF);

  AFieldMaster* new_fm=new ScalarParticleDistributionMaster(&m_tml_global_comm,fieldname,filename,savetype,t_0,t_end,dt,t_snap,x_0,x_max,nx,tag,mask);
  m_save_fields.push_back(new_fm);

  barrier.wait("CLatticeMaster::addTaggedScalarParticleDistributionSaver");

  console.Debug() << "end CLatticeMaster::addTaggedScalarParticleSaveField()\n";
}
