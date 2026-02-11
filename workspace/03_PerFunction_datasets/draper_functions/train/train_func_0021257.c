libnumfixnum_width(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj SCM_SUBRARGS[0];
  int SCM_i;
  SCM_ENTER_SUBR("fixnum-width");
  for (SCM_i=0; SCM_i<0; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  {
{
int SCM_RESULT;

#line 90 "libnum.scm"
SCM_RESULT=(SCM_SMALL_INT_SIZE);
SCM_RETURN(Scm_MakeInteger(SCM_RESULT));
}
  }
}
