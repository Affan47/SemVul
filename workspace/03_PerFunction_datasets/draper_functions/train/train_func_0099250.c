isValidContact(const Vec3& p) const
{
  bool res=true;


  vector<Triangle*>::const_iterator titer=m_triangles.begin();
  while((titer!=m_triangles.end())&&(res)){
    res=!((*titer)->dist(p).first);
    titer++;
  }


  if(res){
    vector<Edge*>::const_iterator eiter=m_edges.begin();
    while((eiter!=m_edges.end())&&(res)){
      res=!((*eiter)->dist(p).first);
      eiter++;
    }
  }
  return res;
}
