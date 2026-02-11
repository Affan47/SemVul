sep(const Vec3& p) const
{
  double sep;

  Vec3 v=m_p1-m_p0;
  Vec3 vu=v.unit();
  double d=((p-m_p0)*vu);
  if((d>0.0)&(d*d<v.norm2())){
    sep=((p-m_p0)-d*vu).norm();
  } else {
    double d1=(p-m_p0).norm();
    double d2=(p-m_p1).norm();
    sep=(d1<d2) ? d1 : d2;
  }

  return sep;
}
