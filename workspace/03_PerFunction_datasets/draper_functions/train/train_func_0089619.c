addTaggedScalarInteractionSaveField(const string& filename, const string& fieldname,const string& igtype,const string& igname,const string& savetype, int t_0,int t_end,int dt,int tag,int mask, bool checked)
{
  console.Debug() << "CLatticeMaster::addTaggedScalarInteractionSaveField(" << filename << ","<< fieldname << "," << igname << "," << t_0 << "," << t_end << "," << dt << ")\n";

  CMPILCmdBuffer cmd_buffer(m_global_comm,m_global_rank);
  CMPIBarrier barrier(m_global_comm);


  cmd_buffer.broadcast(CMD_ADD_SIF);

  AFieldMaster* new_fm=new ScalarInteractionFieldMaster(&m_tml_global_comm,fieldname,igtype,igname,filename,savetype,t_0,t_end,dt,tag,mask,checked);
  m_save_fields.push_back(new_fm);

  barrier.wait("CLatticeMaster::addTaggedScalarInteractionSaveField");

  console.Debug() << "end CLatticeMaster::addTaggedScalarInteractionSaveField()\n";
}
