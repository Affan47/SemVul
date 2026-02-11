libsyssys_time(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj SCM_SUBRARGS[0];
  int SCM_i;
  SCM_ENTER_SUBR("sys-time");
  for (SCM_i=0; SCM_i<0; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  {
{
ScmObj SCM_RESULT;

#line 759 "libsys.scm"
SCM_RESULT=(Scm_MakeSysTime(time(NULL)));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
