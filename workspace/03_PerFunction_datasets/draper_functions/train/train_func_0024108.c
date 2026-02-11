ccR(int i)
{
  cid[i]=ccnt;
  for(list<int>::iterator iter=m_data[i].begin();
      iter!=m_data[i].end();
      iter++){
    if(cid[*iter]==0){
      ccR(*iter);
    }
  }
}
