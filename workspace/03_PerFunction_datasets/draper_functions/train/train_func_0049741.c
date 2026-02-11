CreateIntegerString(char *format, char *str, int k)
{
  int i, j;
  char *buffer;
  for (j=10, i=1; k >= j; j*=10, i++);
  if (format)
    if (str)
      sprintf(buffer=(char*)dw_malloc(strlen(format)+strlen(str)+i-3),format,str,k);
    else
      sprintf(buffer=(char*)dw_malloc(strlen(format)+i-1),format,k);
  else
    sprintf(buffer=(char*)dw_malloc(i+1),"%d",k);
  return buffer;
}
