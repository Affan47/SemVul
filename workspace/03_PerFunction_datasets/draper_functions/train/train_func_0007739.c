AnchorRegex(char *regex, char *out, int outSz)

{
if (EMPTY(regex))
  {
  memset(out,0,outSz);
  }
else
  {
  snprintf(out,outSz,"^(%s)$",regex);
  }
}
