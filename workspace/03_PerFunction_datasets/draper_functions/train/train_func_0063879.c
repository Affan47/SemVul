append(const char *s2) const
{
  GP<GStringRep> retval;
  if(s2)
  {
    retval=concat(data,s2);
  }else
  {
    retval=const_cast<GStringRep *>(this);
  }
  return retval;
}
