gen_libfunc (optab optable, const char *opname, int suffix, enum machine_mode mode)
{
  unsigned opname_len = strlen (opname);
  const char *mname = GET_MODE_NAME (mode);
  unsigned mname_len = strlen (mname);
  char *libfunc_name = XALLOCAVEC (char, 2 + opname_len + mname_len + 1 + 1);
  char *p;
  const char *q;

  p = libfunc_name;
  *p++ = '_';
  *p++ = '_';
  for (q = opname; *q; )
    *p++ = *q++;
  for (q = mname; *q; q++)
    *p++ = TOLOWER (*q);
  *p++ = suffix;
  *p = '\0';

  set_optab_libfunc (optable, mode,
		     ggc_alloc_string (libfunc_name, p - libfunc_name));
}
