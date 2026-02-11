math3d_lib_make_quatf(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj vec_scm;
  ScmObj vec;
  ScmObj angle_scm;
  double angle;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("make-quatf");
  if (SCM_ARGCNT >= 3
      && !SCM_NULLP(SCM_ARGREF(SCM_ARGCNT-1)))
    Scm_Error("too many arguments: up to 2 is expected, %d given.", SCM_ARGCNT + Scm_Length(SCM_ARGREF(SCM_ARGCNT-1)) - 1);
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  if (SCM_ARGCNT > 0+1) {
    vec_scm = SCM_SUBRARGS[0];
  } else {
    vec_scm = SCM_UNBOUND;
  }
  vec = (vec_scm);
  if (SCM_ARGCNT > 1+1) {
    angle_scm = SCM_SUBRARGS[1];
  } else {
    angle_scm = SCM_MAKE_INT(0);
  }
  if (!SCM_REALP(angle_scm)) Scm_Error("real number required, but got %S", angle_scm);
  angle = Scm_GetDouble(angle_scm);
  {
if (SCM_UNBOUNDP(vec)) {
    SCM_RETURN(Scm_MakeQuatf(0.0, 0.0, 0.0, 1.0));
  } else {
    float *q;
    double sint, cost;
    SCM_MATH3D_X3FP(q, vec);
    sint = sin(angle/2.0);
    cost = cos(angle/2.0);
    SCM_RETURN(Scm_MakeQuatf(sint*q[0], sint*q[1], sint*q[2], cost));
  }
  }
}
