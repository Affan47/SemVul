mkostemps64 (template, suffixlen, flags)
     char *template;
     int suffixlen;
     int flags;
{
  if (suffixlen < 0)
    {
      __set_errno (EINVAL);
      return -1;
    }

  return __gen_tempname (template, suffixlen, flags | O_LARGEFILE, __GT_FILE);
}
