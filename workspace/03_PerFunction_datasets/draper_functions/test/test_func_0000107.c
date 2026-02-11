tagEdgeY(int tag1,int tag2,double d)
{
  for(vector<SimpleParticle>::iterator iter=m_bpart.begin();
      iter!=m_bpart.end();
      iter++){
    double py=iter->getPos().Y();
    double r=iter->getRad();
    if(py-m_ymin<r+d) iter->setTag(tag1);
    if(m_ymax-py<r+d) iter->setTag(tag2);
  }
}
