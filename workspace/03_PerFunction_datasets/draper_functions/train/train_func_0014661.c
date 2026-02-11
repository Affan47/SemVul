operator==(const String &rhs) const
{
  return (size() == rhs.size() &&
	  ::strncmp(iImp->iData, rhs.iImp->iData, size()) == 0);
}
