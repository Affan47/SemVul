consistentProperty(const char *lhs, const char *rhs)
{
  if (!lhs && !rhs)
    return true;
  if (!lhs || !rhs)
    return false;
  return strcmp(lhs, rhs) == 0;
}
