endsWith(string const &s1, string const &s2) const
{
  int const limit = s2.size(), constraint = s1.size();

  if(constraint < limit)
  {
    return false;
  }
  for(int i = limit-1, j = constraint - 1; i >= 0; i--, j--)
  {
    if(s1[j] != s2[i])
    {
      return false;
    }
  }

  return true;
}
