math3d_lib_matrix4f_copy(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj m_scm;
  ScmMatrix4f* m;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("matrix4f-copy");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  m_scm = SCM_SUBRARGS[0];
  if (!SCM_MATRIX4FP(m_scm)) Scm_Error("<matrix4f> required, but got %S", m_scm);
  m = SCM_MATRIX4F(m_scm);
  {
{
ScmObj SCM_RESULT;
 SCM_RESULT = (
#line 332 "math3d-lib.stub"
Scm_MakeMatrix4fv(SCM_MATRIX4F_D(m)));
SCM_RETURN(SCM_OBJ_SAFE(SCM_RESULT));
}
  }
}
