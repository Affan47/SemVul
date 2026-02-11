fixstatchar(uchar c)

{
  if (c=='\t' || c<=LAST_TEXTCODE ||
      (c==FORMAT_CODE) || c=='\r' || c=='\n')
    return ' ';
  return c;
}
