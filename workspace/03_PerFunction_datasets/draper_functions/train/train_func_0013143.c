SetFilePosition(FILE *f_in, char *format, char *str)
{
  char *buffer;
  int rtrn;
  if (format)
    sprintf(buffer=(char*)dw_malloc(strlen(format)+strlen(str)-1),format,str);
  else
    buffer=str;
  rtrn=dw_SetFilePosition(f_in,buffer);
  if (buffer != str) dw_free(buffer);
  return rtrn ? 0 : SWITCHIO_LINE_ID_NOT_FOUND;
}
