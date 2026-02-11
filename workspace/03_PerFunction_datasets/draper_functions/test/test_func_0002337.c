isolate_tilde_prefix (fname, lenp)
     const char *fname;
     int *lenp;
{
  char *ret;
  int i;

  ret = (char *)xmalloc (strlen (fname));
#if defined (__MSDOS__)
  for (i = 1; fname[i] && fname[i] != '/' && fname[i] != '\\'; i++)
#else
  for (i = 1; fname[i] && fname[i] != '/'; i++)
#endif
    ret[i - 1] = fname[i];
  ret[i - 1] = '\0';
  if (lenp)
    *lenp = i;
  return ret;
}
