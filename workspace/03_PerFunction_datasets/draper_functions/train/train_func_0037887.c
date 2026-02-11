math3d_lib_matrix4f_TOrotation(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj m_scm;
  ScmMatrix4f* m;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("matrix4f->rotation");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  m_scm = SCM_SUBRARGS[0];
  if (!SCM_MATRIX4FP(m_scm)) Scm_Error("<matrix4f> required, but got %S", m_scm);
  m = SCM_MATRIX4F(m_scm);
  {
float v[4];
  float angle = Scm_Matrix4fToRotationv(SCM_MATRIX4F_D(m), v);
  SCM_RETURN(Scm_Values2(Scm_MakeVector4fv(v), Scm_MakeFlonum((double)angle)));
  }
}
