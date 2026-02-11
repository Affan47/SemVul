getMaxTelephoneLen() const
{
  if (_fromFile)
    return UINT_MAX;
  else
    return _mePhonebook->getMaxTelephoneLen();
}
