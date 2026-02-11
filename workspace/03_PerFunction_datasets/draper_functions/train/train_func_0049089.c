gauche_gdklib_make_gdk_point_vector(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj length_scm;
  int length;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("make-gdk-point-vector");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  length_scm = SCM_SUBRARGS[0];
  if (!SCM_INTP(length_scm)) Scm_Error("small integer required, but got %S", length_scm);
  length = SCM_INT_VALUE(length_scm);
  {
SCM_RETURN(Scm_MakeGdkPointVector(NULL, length));
  }
}
