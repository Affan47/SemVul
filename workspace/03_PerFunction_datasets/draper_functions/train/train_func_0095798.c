libmod_25import_module(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj mod_scm;
  ScmModule* mod;
  ScmObj imported_scm;
  ScmObj imported;
  ScmObj prefix_scm;
  ScmObj prefix;
  ScmObj flags_scm;
  u_long flags;
  ScmObj SCM_SUBRARGS[6];
  int SCM_i;
  SCM_ENTER_SUBR("%import-module");
  if (SCM_ARGCNT >= 5
      && !SCM_NULLP(SCM_ARGREF(SCM_ARGCNT-1)))
    Scm_Error("too many arguments: up to 4 is expected, %d given.", SCM_ARGCNT + Scm_Length(SCM_ARGREF(SCM_ARGCNT-1)) - 1);
  for (SCM_i=0; SCM_i<6; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  mod_scm = SCM_SUBRARGS[0];
  if (!SCM_MODULEP(mod_scm)) Scm_Error("module required, but got %S", mod_scm);
  mod = SCM_MODULE(mod_scm);
  imported_scm = SCM_SUBRARGS[1];
  imported = (imported_scm);
  if (SCM_ARGCNT > 2+1) {
    prefix_scm = SCM_SUBRARGS[2];
  } else {
    prefix_scm = SCM_FALSE;
  }
  prefix = (prefix_scm);
  if (SCM_ARGCNT > 3+1) {
    flags_scm = SCM_SUBRARGS[3];
  } else {
    flags_scm = SCM_MAKE_INT(0);
  }
  if (!SCM_UINTEGERP(flags_scm)) Scm_Error("C integer required, but got %S", flags_scm);
  flags = Scm_GetIntegerU(flags_scm);
  {
{
ScmObj SCM_RESULT;
SCM_RESULT=(Scm_ImportModule(mod,imported,prefix,flags));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
