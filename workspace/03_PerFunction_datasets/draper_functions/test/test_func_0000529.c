getCornerById(int id)
{
  Corner2D* res;

  map<int,int>::iterator it=m_corner_by_id.find(id);
  if(it!=m_corner_by_id.end()){
    res=&(m_corners[it->second]);
  } else {
    res=NULL;
  }

  return res;
}
