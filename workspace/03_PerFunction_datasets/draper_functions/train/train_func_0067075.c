libsyssys_tmpnam(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj SCM_SUBRARGS[0];
  int SCM_i;
  SCM_ENTER_SUBR("sys-tmpnam");
  for (SCM_i=0; SCM_i<0; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  {
{
ScmObj SCM_RESULT;

#line 393 "libsys.scm"

#if HAVE_MKSTEMP

#line 394 "libsys.scm"
{char nam[]="/tmp/fileXXXXXX";int fd;
SCM_SYSCALL(fd,mkstemp(nam));
if ((fd)<(0)){{Scm_SysError("mkstemp failed");}}
close(fd);
unlink(nam);
SCM_RESULT=(SCM_MAKE_STR_COPYING(nam));}
#else

#line 400 "libsys.scm"
{char* s=tmpnam(NULL);
SCM_RESULT=(SCM_MAKE_STR_COPYING(s));}
#endif

SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
