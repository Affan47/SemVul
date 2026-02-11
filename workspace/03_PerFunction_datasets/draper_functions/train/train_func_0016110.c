math3d_lib_axes_TOquatf(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj v1_scm;
  ScmVector4f* v1;
  ScmObj v2_scm;
  ScmVector4f* v2;
  ScmObj w1_scm;
  ScmVector4f* w1;
  ScmObj w2_scm;
  ScmVector4f* w2;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("axes->quatf");
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  v1_scm = SCM_SUBRARGS[0];
  if (!SCM_VECTOR4FP(v1_scm)) Scm_Error("<vector4f> required, but got %S", v1_scm);
  v1 = SCM_VECTOR4F(v1_scm);
  v2_scm = SCM_SUBRARGS[1];
  if (!SCM_VECTOR4FP(v2_scm)) Scm_Error("<vector4f> required, but got %S", v2_scm);
  v2 = SCM_VECTOR4F(v2_scm);
  w1_scm = SCM_SUBRARGS[2];
  if (!SCM_VECTOR4FP(w1_scm)) Scm_Error("<vector4f> required, but got %S", w1_scm);
  w1 = SCM_VECTOR4F(w1_scm);
  w2_scm = SCM_SUBRARGS[3];
  if (!SCM_VECTOR4FP(w2_scm)) Scm_Error("<vector4f> required, but got %S", w2_scm);
  w2 = SCM_VECTOR4F(w2_scm);
  {
{
ScmObj SCM_RESULT;

#line 772 "math3d-lib.stub"
{float r[4];
Scm_AxesToQuatfv(r,SCM_VECTOR4F_D(v1),SCM_VECTOR4F_D(v2),
SCM_VECTOR4F_D(w1),SCM_VECTOR4F_D(w2));
SCM_RESULT=(Scm_MakeQuatfv(r));}
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
