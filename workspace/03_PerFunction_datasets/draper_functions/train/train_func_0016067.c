destroyArrays() {
  if (m_param)
    {
      int i;
      for (i = 0; i < m_uniformCount; i++){
        if(m_param[i])delete[]m_param[i];
        m_param[i]=NULL;
      }
    }

  if (m_size)   delete[]m_size;   m_size   =NULL;
  if (m_type)   delete[]m_type;   m_type   =NULL;
  if (m_symname)delete[]m_symname;m_symname=NULL;
  if (m_flag)   delete[]m_flag;   m_flag   =NULL;
  if (m_loc)    delete[]m_loc;    m_loc    =NULL;
  if (m_param)  delete[]m_param;  m_param  =NULL;
}
