Off(const map<int,Vec3>& data)
{
  bool res=false;

  map<int,Vec3>::const_iterator iter=data.begin();
  while ((iter!=data.end()) && !res){
    double m=iter->second.norm();

    res=(m>m_off_level);
    iter++;
  }
  return !res;
}
