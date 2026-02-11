search(char c, int from) const
{
  if (from<0)
    from += size;
  int retval=(-1);
  if (from>=0 && from<size)
  {
    char const *const s = strchr(data+from,c);
    if(s)
      retval=(int)((size_t)s-(size_t)data);
  }
  return retval;
}
