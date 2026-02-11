libioread_list(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj closer_scm;
  ScmChar closer;
  ScmObj port_scm;
  ScmObj port;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("read-list");
  if (SCM_ARGCNT >= 3
      && !SCM_NULLP(SCM_ARGREF(SCM_ARGCNT-1)))
    Scm_Error("too many arguments: up to 2 is expected, %d given.", SCM_ARGCNT + Scm_Length(SCM_ARGREF(SCM_ARGCNT-1)) - 1);
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  closer_scm = SCM_SUBRARGS[0];
  if (!SCM_CHARP(closer_scm)) Scm_Error("character required, but got %S", closer_scm);
  closer = SCM_CHAR_VALUE(closer_scm);
  if (SCM_ARGCNT > 1+1) {
    port_scm = SCM_SUBRARGS[1];
  } else {
    port_scm = SCM_OBJ(SCM_CURIN);
  }
  port = (port_scm);
  {
{
ScmObj SCM_RESULT;

#line 419 "libio.scm"
SCM_RESULT=(Scm_ReadList(port,closer));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
