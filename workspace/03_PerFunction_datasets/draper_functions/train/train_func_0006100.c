gfs_restore_floating_point_exceptions (void)
{
#ifdef EXCEPTIONS
  int ret = fetestexcept (EXCEPTIONS);
  feclearexcept (EXCEPTIONS);
  if (!disabled_fpe)
    feenableexcept (EXCEPTIONS);
  return ret;
#else
  return 0;
#endif
}
