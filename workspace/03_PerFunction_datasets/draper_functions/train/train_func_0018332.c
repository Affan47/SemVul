gdkvisual_gdk_visual_get_best_with_type(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj visual_type_scm;
  int visual_type;
  ScmObj SCM_SUBRARGS[1];
  int SCM_i;
  SCM_ENTER_SUBR("gdk-visual-get-best-with-type");
  for (SCM_i=0; SCM_i<1; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  visual_type_scm = SCM_SUBRARGS[0];
  if (!SCM_INTEGERP(visual_type_scm)) Scm_Error("C integer required, but got %S", visual_type_scm);
  visual_type = Scm_GetInteger(visual_type_scm);
  {
{
GdkVisual* SCM_RESULT;
SCM_RESULT = gdk_visual_get_best_with_type(visual_type);
SCM_RETURN(SCM_MAKE_GDK_VISUAL(SCM_RESULT));
}
  }
}
