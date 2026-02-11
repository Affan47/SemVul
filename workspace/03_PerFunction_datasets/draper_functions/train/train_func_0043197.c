vmprintf(aVL, aFormat, aArgList)
  va_list  aArgList;
     long  aVL;
     char *aFormat;
{
  int  retVal;


  if (aVL <= util_VL) {
    retVal = vfprintf (stdout, aFormat, aArgList);
  } else {
    retVal = 0;
  }

  return (retVal);
}
