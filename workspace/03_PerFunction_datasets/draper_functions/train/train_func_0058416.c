math3d_lib_quatf_set4X(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj q_scm;
  ScmQuatf* q;
  ScmObj x_scm;
  double x;
  ScmObj y_scm;
  double y;
  ScmObj z_scm;
  double z;
  ScmObj w_scm;
  double w;
  ScmObj SCM_SUBRARGS[5];
  int SCM_i;
  SCM_ENTER_SUBR("quatf-set4!");
  for (SCM_i=0; SCM_i<5; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  q_scm = SCM_SUBRARGS[0];
  if (!SCM_QUATFP(q_scm)) Scm_Error("<quatf> required, but got %S", q_scm);
  q = SCM_QUATF(q_scm);
  x_scm = SCM_SUBRARGS[1];
  if (!SCM_REALP(x_scm)) Scm_Error("real number required, but got %S", x_scm);
  x = Scm_GetDouble(x_scm);
  y_scm = SCM_SUBRARGS[2];
  if (!SCM_REALP(y_scm)) Scm_Error("real number required, but got %S", y_scm);
  y = Scm_GetDouble(y_scm);
  z_scm = SCM_SUBRARGS[3];
  if (!SCM_REALP(z_scm)) Scm_Error("real number required, but got %S", z_scm);
  z = Scm_GetDouble(z_scm);
  w_scm = SCM_SUBRARGS[4];
  if (!SCM_REALP(w_scm)) Scm_Error("real number required, but got %S", w_scm);
  w = Scm_GetDouble(w_scm);
  {
{
ScmObj SCM_RESULT;

#line 647 "math3d-lib.stub"
(SCM_QUATF_D(q))[0]=(x),
(SCM_QUATF_D(q))[1]=(y),
(SCM_QUATF_D(q))[2]=(z),
(SCM_QUATF_D(q))[3]=(w);

#line 651 "math3d-lib.stub"
SCM_RESULT=(SCM_OBJ(q));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
