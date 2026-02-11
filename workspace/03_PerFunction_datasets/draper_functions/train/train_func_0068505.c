gdkimage_gdk_image_new(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj type_scm;
  int type;
  ScmObj visual_scm;
  GdkVisual* visual;
  ScmObj width_scm;
  int width;
  ScmObj height_scm;
  int height;
  ScmObj SCM_SUBRARGS[4];
  int SCM_i;
  SCM_ENTER_SUBR("gdk-image-new");
  for (SCM_i=0; SCM_i<4; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  type_scm = SCM_SUBRARGS[0];
  if (!SCM_INTEGERP(type_scm)) Scm_Error("C integer required, but got %S", type_scm);
  type = Scm_GetInteger(type_scm);
  visual_scm = SCM_SUBRARGS[1];
  if (!SCM_GDK_VISUAL_P(visual_scm)) Scm_Error("<gdk-visual> required, but got %S", visual_scm);
  visual = SCM_GDK_VISUAL(visual_scm);
  width_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(width_scm)) Scm_Error("C integer required, but got %S", width_scm);
  width = Scm_GetInteger(width_scm);
  height_scm = SCM_SUBRARGS[3];
  if (!SCM_INTEGERP(height_scm)) Scm_Error("C integer required, but got %S", height_scm);
  height = Scm_GetInteger(height_scm);
  {
{
GdkImage* SCM_RESULT;
SCM_RESULT = gdk_image_new(type, visual, width, height);
SCM_RETURN(SCM_MAKE_GDK_IMAGE(SCM_RESULT));
}
  }
}
