tilesMess(int w, int h)
{
  if(m_minVals) delete[]m_minVals;
  if(m_maxVals) delete[]m_maxVals;

  if(w>0)m_xtiles=w;
  if(h>0)m_ytiles=h;

  m_minVals=new unsigned char[4*m_xtiles*m_ytiles];
  m_maxVals=new unsigned char[4*m_xtiles*m_ytiles];

  setPixModified();
}
