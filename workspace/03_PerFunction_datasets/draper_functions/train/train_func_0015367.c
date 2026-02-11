math3d_lib_make_vector4f_array(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj len_scm;
  int len;
  ScmObj init_scm;
  ScmObj init;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("make-vector4f-array");
  if (SCM_ARGCNT >= 3
      && !SCM_NULLP(SCM_ARGREF(SCM_ARGCNT-1)))
    Scm_Error("too many arguments: up to 2 is expected, %d given.", SCM_ARGCNT + Scm_Length(SCM_ARGREF(SCM_ARGCNT-1)) - 1);
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  len_scm = SCM_SUBRARGS[0];
  if (!SCM_INTP(len_scm)) Scm_Error("small integer required, but got %S", len_scm);
  len = SCM_INT_VALUE(len_scm);
  if (SCM_ARGCNT > 1+1) {
    init_scm = SCM_SUBRARGS[1];
  } else {
    init_scm = SCM_UNBOUND;
  }
  init = (init_scm);
  {
ScmObj va = SCM_FALSE;
  if (len < 0) Scm_Error("vector4f-array length must be positive: %d", len);
  if (SCM_VECTOR4FP(init)) {
    va = Scm_MakeVector4fArrayv(len, SCM_VECTOR4F_D(init));
  } else if (SCM_UNBOUNDP(init)) {
    va = Scm_MakeVector4fArrayv(len, NULL);
  } else {
    Scm_Error("bad initializer for vector array: must be <vector4f>, but got %S", init);
  }
  SCM_RETURN(va);
  }
}
