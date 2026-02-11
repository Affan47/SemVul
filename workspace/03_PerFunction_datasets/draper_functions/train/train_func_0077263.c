scm_srcprops_to_plist (SCM obj)
{
  SCM plist = SRCPROPPLIST (obj);
  if (!SCM_UNBNDP (SRCPROPCOPY (obj)))
    plist = scm_acons (scm_sym_copy, SRCPROPCOPY (obj), plist);
  plist = scm_acons (scm_sym_column, scm_from_int (SRCPROPCOL (obj)), plist);
  plist = scm_acons (scm_sym_line, scm_from_int (SRCPROPLINE (obj)), plist);
  plist = scm_acons (scm_sym_breakpoint, scm_from_bool (SRCPROPBRK (obj)), plist);
  return plist;
}
