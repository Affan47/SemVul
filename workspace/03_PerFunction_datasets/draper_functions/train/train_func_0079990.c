MET_SetFileSuffix(char *_fName, const char *_suf)
  {
  int i;
  MET_GetFileSuffixPtr(_fName, &i);
  if(i>0)
    {
    if(_suf[0] == '.')
      _fName[i-1] = '\0';
    else
      _fName[i] = '\0';
    strcat(_fName, _suf);
    return true;
    }
  else
    {
    if( _suf[0] != '.')
      {
      strcat(_fName, ".");
      }
    strcat(_fName, _suf);
    return true;
    }
  }
