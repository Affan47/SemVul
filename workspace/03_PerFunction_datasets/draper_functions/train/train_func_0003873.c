math3d_lib_point4f_array_TOf32vector(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj a_scm;
  ScmPoint4fArray* a;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("point4f-array->f32vector");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  a_scm = SCM_SUBRARGS[0];
  if (!SCM_POINT4F_ARRAY_P(a_scm)) Scm_Error("<point4f-array> required, but got %S", a_scm);
  a = SCM_POINT4F_ARRAY(a_scm);
  {
SCM_RETURN(Scm_MakeF32VectorFromArray(SCM_POINT4F_ARRAY_SIZE(a)*4,
                                         SCM_POINT4F_ARRAY_D(a)));
  }
}
