raise_scheme_exception_prelude(long why, long nargs)
{
  s48_setup_external_exception(why, nargs);

  if (11 < nargs) {
    fprintf(stderr, "too many arguments to external exception, discarding surplus\n");
    nargs = 11;
  }
  return nargs;
}
