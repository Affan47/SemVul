libeval_25internal_macro_expand(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj form_scm;
  ScmObj form;
  ScmObj env_scm;
  ScmObj env;
  ScmObj once_scm;
  int once;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("%internal-macro-expand");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  form_scm = SCM_SUBRARGS[0];
  form = (form_scm);
  env_scm = SCM_SUBRARGS[1];
  env = (env_scm);
  once_scm = SCM_SUBRARGS[2];
  if (!SCM_BOOLP(once_scm)) Scm_Error("boolean required, but got %S", once_scm);
  once = SCM_BOOL_VALUE(once_scm);
  {
{
ScmObj SCM_RESULT;
SCM_RESULT=(Scm_VMMacroExpand(form,env,once));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
