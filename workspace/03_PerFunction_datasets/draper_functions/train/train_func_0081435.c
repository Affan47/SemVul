math3d_lib_vector4f_subX(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj x_scm;
  ScmVector4f* x;
  ScmObj y_scm;
  ScmVector4f* y;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("vector4f-sub!");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  x_scm = SCM_SUBRARGS[0];
  if (!SCM_VECTOR4FP(x_scm)) Scm_Error("<vector4f> required, but got %S", x_scm);
  x = SCM_VECTOR4F(x_scm);
  y_scm = SCM_SUBRARGS[1];
  if (!SCM_VECTOR4FP(y_scm)) Scm_Error("<vector4f> required, but got %S", y_scm);
  y = SCM_VECTOR4F(y_scm);
  {
Scm_Vector4fSubv(SCM_VECTOR4F_D(x), SCM_VECTOR4F_D(x), SCM_VECTOR4F_D(y));
  SCM_RETURN(SCM_OBJ(x));
  }
}
