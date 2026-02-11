getInteractions(set<BasicInteraction,BILess>& iset, double dmax)
{
  for(int i=0;i<m_xsize;i++){
    for(int j=0;j<m_ysize;j++){
      for(int k=0;k<m_zsize;k++){
        int idx=i+m_xsize*j+k*m_xsize*m_ysize;

        if(m_data[idx].size()>=2){
          for(vector<SimpleParticle>::iterator iter=m_data[idx].begin();
              iter!=m_data[idx].end()-1;
              iter++)
          {
            for (
              vector<SimpleParticle>::iterator iter2=iter+1;
              iter2!=m_data[idx].end();
              iter2++)
            {

              if((iter->getPos()-iter2->getPos()).norm() < dmax*(iter->getRad()+iter2->getRad()))
              {
                iset.insert(BasicInteraction(iter->getID(),iter2->getID()));
              }
            }
          }
        }
      }
    }
  }
}
