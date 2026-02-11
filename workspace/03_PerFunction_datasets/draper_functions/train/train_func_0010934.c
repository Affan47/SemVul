AsnOidCompare(AsnOid *o1, AsnOid *o2)
{
  int result;

  if(o1->octetLen > o2->octetLen)
  {
    result = memcmp(o1->octs, o2->octs, o2->octetLen);
    if(result < 0)
      return AsnOidLess;
    else
      return AsnOidGreater;
  } else if(o1->octetLen < o2->octetLen)
  {
    result = memcmp(o1->octs, o2->octs, o1->octetLen);
    if(result > 0)
      return AsnOidGreater;
    else if(result == 0)
      return AsnOidRoot;
    else
      return AsnOidLess;
  } else
  {
    result = memcmp(o1->octs, o2->octs, o1->octetLen);
    if(result < 0)
      return AsnOidLess;
    else if(result == 0)
      return AsnOidEqual;
    else
      return AsnOidGreater;
  }
}
