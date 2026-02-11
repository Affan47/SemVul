fread_string(gbfile* fd)
{
  char* val;
  int len = fread_integer(fd);

  if (len == 0) {
    return NULL;
  }

  val = (char*) xmalloc(len+1);
  gbfread(val, 1, len, fd);
  while (len != 0 && val[len-1] == ' ') {
    len--;
  }
  val[len] = 0;
  return val;
}
