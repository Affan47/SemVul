operator==(const COMMON_COMPONENT& x)const
{
  const COMMON_LOGIC* p = dynamic_cast<const COMMON_LOGIC*>(&x);
  bool rv = p
    && incount == p->incount
    && COMMON_COMPONENT::operator==(x);
  if (rv) {
  }else{
  }
  return rv;
}
