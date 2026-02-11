math3d_lib_quatf_scaleX(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj q_scm;
  ScmQuatf* q;
  ScmObj s_scm;
  double s;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("quatf-scale!");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  q_scm = SCM_SUBRARGS[0];
  if (!SCM_QUATFP(q_scm)) Scm_Error("<quatf> required, but got %S", q_scm);
  q = SCM_QUATF(q_scm);
  s_scm = SCM_SUBRARGS[1];
  if (!SCM_REALP(s_scm)) Scm_Error("real number required, but got %S", s_scm);
  s = Scm_GetDouble(s_scm);
  {
float *d = SCM_QUATF_D(q);
  if (s == 0.0) Scm_Error("divide by zero");
  d[0] /= s; d[1] /= s; d[2] /= s; d[3] /= s;
  SCM_RETURN(SCM_OBJ(q));
  }
}
