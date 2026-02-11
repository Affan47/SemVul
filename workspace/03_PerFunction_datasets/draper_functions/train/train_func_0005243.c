math3d_lib_matrix4f_TOquatfX(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj q_scm;
  ScmQuatf* q;
  ScmObj m_scm;
  ScmMatrix4f* m;
  ScmObj SCM_SUBRARGS[2];
  int SCM_i;
  SCM_ENTER_SUBR("matrix4f->quatf!");
  for (SCM_i=0; SCM_i<2; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  q_scm = SCM_SUBRARGS[0];
  if (!SCM_QUATFP(q_scm)) Scm_Error("<quatf> required, but got %S", q_scm);
  q = SCM_QUATF(q_scm);
  m_scm = SCM_SUBRARGS[1];
  if (!SCM_MATRIX4FP(m_scm)) Scm_Error("<matrix4f> required, but got %S", m_scm);
  m = SCM_MATRIX4F(m_scm);
  {
{
ScmObj SCM_RESULT;

#line 741 "math3d-lib.stub"
Scm_Matrix4fToQuatfv(SCM_QUATF_D(q),SCM_MATRIX4F_D(m));

#line 742 "math3d-lib.stub"
SCM_RESULT=(SCM_OBJ(q));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
