chash_dup(const void * data, unsigned int len)
{
  void * r;

  r = (char *) malloc(len);
  if (!r)
    return NULL;
  memcpy(r, data, len);
  return r;
}
