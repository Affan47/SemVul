growTo(int size)
{
  if(size>m_vbuffersize){
    char *temp=m_vbuffer;
    m_vbuffersize=size;
    m_vbuffer=new char[m_vbuffersize];
    memcpy((void*)m_vbuffer,(void*)temp,size_t(m_position));
    delete temp;
  }
}
