libsyssys_lchown(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj path_scm;
  const char * path;
  ScmObj owner_scm;
  int owner;
  ScmObj group_scm;
  int group;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("sys-lchown");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  path_scm = SCM_SUBRARGS[0];
  if (!SCM_STRINGP(path_scm)) Scm_Error("const C string required, but got %S", path_scm);
  path = SCM_STRING_CONST_CSTRING(path_scm);
  owner_scm = SCM_SUBRARGS[1];
  if (!SCM_INTEGERP(owner_scm)) Scm_Error("C integer required, but got %S", owner_scm);
  owner = Scm_GetInteger(owner_scm);
  group_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(group_scm)) Scm_Error("C integer required, but got %S", group_scm);
  group = Scm_GetInteger(group_scm);
  {
{
int SCM_RESULT;

#line 854 "libsys.scm"
SCM_SYSCALL(SCM_RESULT,lchown(path,owner,group));

#line 855 "libsys.scm"
if ((SCM_RESULT)<(0)){{Scm_SysError("lchown failed on %S",path);}}
SCM_RETURN(Scm_MakeInteger(SCM_RESULT));
}
  }
}
