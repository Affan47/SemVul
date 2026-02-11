StripListSep(char *strList, char *outBuf, int outBufSz)
{
  memset(outBuf,0,outBufSz);

  if(EMPTY(strList))
    {
    return false;
    }

  if(strList[0] != '{')
    {
    return false;
    }

  snprintf(outBuf,outBufSz,"%s",strList + 1);

  if(outBuf[strlen(outBuf) - 1] == '}')
    {
    outBuf[strlen(outBuf) - 1] = '\0';
    }

  return true;
}
