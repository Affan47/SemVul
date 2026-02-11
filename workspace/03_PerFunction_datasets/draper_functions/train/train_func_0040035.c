libobjis_aP(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj obj_scm;
  ScmObj obj;
  ScmObj klass_scm;
  ScmClass* klass;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("is-a?");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  obj_scm = SCM_SUBRARGS[0];
  obj = (obj_scm);
  klass_scm = SCM_SUBRARGS[1];
  if (!SCM_CLASSP(klass_scm)) Scm_Error("class required, but got %S", klass_scm);
  klass = SCM_CLASS(klass_scm);
  {
{
ScmObj SCM_RESULT;
SCM_RESULT=(Scm_VMIsA(obj,klass));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
