_dmalloc_memchr(const char *file, const int line,
			 const void *s1, const int ch, const DMALLOC_SIZE len)
{
  if (BIT_IS_SET(_dmalloc_flags, DEBUG_CHECK_FUNCS)) {
    if (! dmalloc_verify_pnt(file, line, "memchr", s1,
			     0 , len)) {
      dmalloc_message("bad pointer argument found in memchr");
    }
  }
  return (void *)memchr(s1, ch, len);
}
