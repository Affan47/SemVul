mystrdup(struct InputStream *is,const char *src) {
  size_t  len;
  char	  *dst;

  if (src==NULL)
    return NULL;

  len = strlen(src);
  dst = is->memalloc(is,len+1);
  if (dst==NULL)
    return NULL;

  memcpy(dst,src,len+1);

  return dst;
}
