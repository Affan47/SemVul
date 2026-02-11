CopyStr(char **src,char **dst) {
  size_t l;

  if (!*src)
    return;

  l = strlen(*src)+1;
  memcpy(*dst,*src,l);
  *src = *dst;
  *dst += l;
}
