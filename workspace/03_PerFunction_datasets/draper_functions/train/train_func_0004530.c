libmiscwarn(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj fmt_scm;
  ScmString* fmt;
  ScmObj args_scm;
  ScmObj args;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("warn");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  fmt_scm = SCM_SUBRARGS[0];
  if (!SCM_STRINGP(fmt_scm)) Scm_Error("string required, but got %S", fmt_scm);
  fmt = SCM_STRING(fmt_scm);
  args_scm = SCM_SUBRARGS[SCM_ARGCNT-1];
  args = (args_scm);
  {
Scm_FWarn(fmt,args);
SCM_RETURN(SCM_UNDEFINED);
  }
}
