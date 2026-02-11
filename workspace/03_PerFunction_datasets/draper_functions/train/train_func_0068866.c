gen_intraclass_conv_libfunc (convert_optab tab, const char *opname,
			     enum machine_mode tmode, enum machine_mode fmode)
{
  size_t opname_len = strlen (opname);
  size_t mname_len = 0;

  const char *fname, *tname;
  const char *q;
  char *nondec_name, *dec_name, *nondec_suffix, *dec_suffix;
  char *libfunc_name, *suffix;
  char *p;


  const size_t dec_len = sizeof (DECIMAL_PREFIX) - 1;

  mname_len = strlen (GET_MODE_NAME (tmode)) + strlen (GET_MODE_NAME (fmode));

  nondec_name = XALLOCAVEC (char, 2 + opname_len + mname_len + 1 + 1);
  nondec_name[0] = '_';
  nondec_name[1] = '_';
  memcpy (&nondec_name[2], opname, opname_len);
  nondec_suffix = nondec_name + opname_len + 2;

  dec_name = XALLOCAVEC (char, 2 + dec_len + opname_len + mname_len + 1 + 1);
  dec_name[0] = '_';
  dec_name[1] = '_';
  memcpy (&dec_name[2], DECIMAL_PREFIX, dec_len);
  memcpy (&dec_name[2 + dec_len], opname, opname_len);
  dec_suffix = dec_name + dec_len + opname_len + 2;

  fname = GET_MODE_NAME (fmode);
  tname = GET_MODE_NAME (tmode);

  if (DECIMAL_FLOAT_MODE_P(fmode) || DECIMAL_FLOAT_MODE_P(tmode))
    {
      libfunc_name = dec_name;
      suffix = dec_suffix;
    }
  else
    {
      libfunc_name = nondec_name;
      suffix = nondec_suffix;
    }

  p = suffix;
  for (q = fname; *q; p++, q++)
    *p = TOLOWER (*q);
  for (q = tname; *q; p++, q++)
    *p = TOLOWER (*q);

  *p++ = '2';
  *p = '\0';

  set_conv_libfunc (tab, tmode, fmode,
		    ggc_alloc_string (libfunc_name, p - libfunc_name));
}
