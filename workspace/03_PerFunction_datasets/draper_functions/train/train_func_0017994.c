getBaseType(void) const
{
  if (!myBaseType.empty()) {
    return myBaseType.c_str();
  }
  else {
    return myType.c_str();
  }
}
