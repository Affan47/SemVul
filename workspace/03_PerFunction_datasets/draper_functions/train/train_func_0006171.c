coneToVectorList(Cone2 const &c, IntegerMatrix const &rays)
{
  IntegerVectorList ret;

  for(Cone::const_iterator i=c.begin();i!=c.end();i++)
    ret.push_back(rays[*i]);

  return ret;
}
