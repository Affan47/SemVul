xmem_cd_iconv (const char *src, size_t srclen, iconv_t cd,
               char **resultp, size_t *lengthp)
{
  int retval = mem_cd_iconv (src, srclen, cd, resultp, lengthp);

  if (retval < 0 && errno == ENOMEM)
    xalloc_die ();
  return retval;
}
