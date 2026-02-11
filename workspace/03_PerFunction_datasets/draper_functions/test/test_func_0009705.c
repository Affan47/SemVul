math3d_lib_vector4f_divX(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj x_scm;
  ScmVector4f* x;
  ScmObj f_scm;
  double f;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("vector4f-div!");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  x_scm = SCM_SUBRARGS[0];
  if (!SCM_VECTOR4FP(x_scm)) Scm_Error("<vector4f> required, but got %S", x_scm);
  x = SCM_VECTOR4F(x_scm);
  f_scm = SCM_SUBRARGS[1];
  if (!SCM_REALP(f_scm)) Scm_Error("real number required, but got %S", f_scm);
  f = Scm_GetDouble(f_scm);
  {
{
ScmObj SCM_RESULT;

#line 149 "math3d-lib.stub"
{SCM_VECTOR4F_REF(x,0)=((SCM_VECTOR4F_REF(x,0))/(f));SCM_VECTOR4F_REF(x,1)=((SCM_VECTOR4F_REF(x,1))/(f));SCM_VECTOR4F_REF(x,2)=((SCM_VECTOR4F_REF(x,2))/(f));SCM_VECTOR4F_REF(x,3)=((SCM_VECTOR4F_REF(x,3))/(f));}

#line 151 "math3d-lib.stub"
return (SCM_OBJ(x));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
