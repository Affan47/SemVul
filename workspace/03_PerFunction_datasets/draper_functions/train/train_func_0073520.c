s48_setup_external_exception(long why_1029X, long nargs_1030X)
{

 {push_exception_setupB(why_1029X, 1);
  if ((10 < nargs_1030X)) {
    ps_error("too many arguments from external exception", 0);
    goto L30898;}
  else {
    goto L30898;}}
 L30898: {
  Sexternal_exception_nargsS = nargs_1030X;
  Sexternal_exceptionPS = 1;
  return;}
}
