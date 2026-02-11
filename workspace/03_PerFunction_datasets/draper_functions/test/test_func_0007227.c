create(const GP<GStringRep> &s1,const GP<GStringRep> &s2)
{
  GStringRep::Native dummy;
  return dummy.concat(s1,s2);
}
