termiolib_sys_tcsendbreak(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj port_or_fd_scm;
  ScmObj port_or_fd;
  ScmObj duration_scm;
  int duration;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("sys-tcsendbreak");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  port_or_fd_scm = SCM_SUBRARGS[0];
  port_or_fd = (port_or_fd_scm);
  duration_scm = SCM_SUBRARGS[1];
  if (!SCM_INTP(duration_scm)) Scm_Error("small integer required, but got %S", duration_scm);
  duration = SCM_INT_VALUE(duration_scm);
  {
{
int SCM_RESULT;

#line 87 "termiolib.stub"
{int fd=Scm_GetPortFd(port_or_fd,TRUE);
SCM_RESULT=((tcsendbreak(fd,duration))>=(0));}
SCM_RETURN(SCM_MAKE_BOOL(SCM_RESULT));
}
  }
}
