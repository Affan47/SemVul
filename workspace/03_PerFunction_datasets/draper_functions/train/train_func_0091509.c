netlib_sockaddr_family1428(ScmNextMethod *nm_, ScmObj *SCM_FP, int SCM_ARGCNT, void *d_)
{
  ScmObj addr_scm;
  ScmObj addr;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  addr_scm = SCM_SUBRARGS[0];
  addr = (addr_scm);
  {
{
ScmObj SCM_RESULT;

#line 56 "netlib.stub"
SCM_RESULT=(scm__rc.d1429[0]);
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
