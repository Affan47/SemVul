libmod_25insert_binding(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj mod_scm;
  ScmModule* mod;
  ScmObj name_scm;
  ScmSymbol* name;
  ScmObj value_scm;
  ScmObj value;
  ScmObj flags_scm;
  ScmObj flags;
  ScmObj SCM_SUBRARGS[5];
  int SCM_i;
  SCM_ENTER_SUBR("%insert-binding");
  if (SCM_ARGCNT >= 5
      && !SCM_NULLP(SCM_ARGREF(SCM_ARGCNT-1)))
    Scm_Error("too many arguments: up to 4 is expected, %d given.", SCM_ARGCNT + Scm_Length(SCM_ARGREF(SCM_ARGCNT-1)) - 1);
  for (SCM_i=0; SCM_i<5; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  mod_scm = SCM_SUBRARGS[0];
  if (!SCM_MODULEP(mod_scm)) Scm_Error("module required, but got %S", mod_scm);
  mod = SCM_MODULE(mod_scm);
  name_scm = SCM_SUBRARGS[1];
  if (!SCM_SYMBOLP(name_scm)) Scm_Error("symbol required, but got %S", name_scm);
  name = SCM_SYMBOL(name_scm);
  value_scm = SCM_SUBRARGS[2];
  value = (value_scm);
  if (SCM_ARGCNT > 3+1) {
    flags_scm = SCM_SUBRARGS[3];
  } else {
    flags_scm = SCM_OBJ(&scm__rc.d1123[5]);
  }
  flags = (flags_scm);
  {
{
ScmObj SCM_RESULT;

#line 131 "libmod.scm"
{int z=0;
if (!(SCM_FALSEP(Scm_Memq(scm__rc.d1123[7],flags)))){{
(z)|=(SCM_BINDING_CONST);}}
if (!(SCM_FALSEP(Scm_Memq(scm__rc.d1123[8],flags)))){{
(z)|=(SCM_BINDING_INLINABLE);}}
SCM_RESULT=(SCM_OBJ(Scm_MakeBinding(mod,name,value,z)));}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
