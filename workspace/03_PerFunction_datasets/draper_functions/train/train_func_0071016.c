MET_GetFileSuffixPtr(const char *_fName, int *i)
  {
  *i = static_cast<int>( strlen(_fName) );
  int j = *i - 5;
  if(j<0)
    {
    j = 0;
    }
  while(*i>j)
    {
    if(_fName[(*i)-1] == '.')
      {
      return true;
      }
    else
      {
      (*i)--;
      }
    }
  *i = 0;
  return false;
  }
