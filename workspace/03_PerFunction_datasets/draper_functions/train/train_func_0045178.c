getInfo(const DataMap *& info, UErrorCode &) const
{
  if(fInfo) {
    info = fInfo;
    return TRUE;
  } else {
    info = NULL;
    return FALSE;
  }
}
