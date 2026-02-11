gauche__syslogsys_syslog(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj prio_scm;
  int prio;
  ScmObj message_scm;
  const char * message;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("sys-syslog");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  prio_scm = SCM_SUBRARGS[0];
  if (!SCM_INTP(prio_scm)) Scm_Error("small integer required, but got %S", prio_scm);
  prio = SCM_INT_VALUE(prio_scm);
  message_scm = SCM_SUBRARGS[1];
  if (!SCM_STRINGP(message_scm)) Scm_Error("const C string required, but got %S", message_scm);
  message = SCM_STRING_CONST_CSTRING(message_scm);
  {

#line 57 "./syslog.scm"

#if defined(HAVE_SYSLOG)

#line 57 "./syslog.scm"
syslog(prio,"%s",message);
#endif

SCM_RETURN(SCM_UNDEFINED);
  }
}
