fread_fixedstring(gbfile* fd, int len)
{
  char* val = (char*) xmalloc(len+1);

  gbfread(val, 1, len, fd);
  while (len != 0 && val[len-1] == ' ') {
    len--;
  }
  val[len] = 0;
  return val;
}
