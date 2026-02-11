libsyssys_fstat(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj port_or_fd_scm;
  ScmObj port_or_fd;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("sys-fstat");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  port_or_fd_scm = SCM_SUBRARGS[0];
  port_or_fd = (port_or_fd_scm);
  {
{
ScmObj SCM_RESULT;

#line 651 "libsys.scm"
{ScmSysStat* s=SCM_SYS_STAT(Scm_MakeSysStat());int fd=
Scm_GetPortFd(port_or_fd,FALSE);int r;
#line 654 "libsys.scm"
if ((fd)<(0)){SCM_RESULT=(SCM_FALSE);} else {
SCM_SYSCALL(r,fstat(fd,SCM_SYS_STAT_STAT(s)));
if ((r)<(0)){{Scm_SysError("fstat failed for %d",fd);}}
SCM_RESULT=(SCM_OBJ(s));}}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
