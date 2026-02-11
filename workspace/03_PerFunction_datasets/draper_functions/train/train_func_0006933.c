getSystemData(GroveString &str) const
{
  if (iter_.type() != TextItem::sdata)
    return accessNotInClass;
  size_t len;
  const Char *ptr = iter_.chars(len);
  str.assign(ptr, len);
  return accessOK;
}
