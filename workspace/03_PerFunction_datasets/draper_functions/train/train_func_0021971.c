gdkdrawable_gdk_draw_line(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj drawable_scm;
  GdkDrawable* drawable;
  ScmObj gc_scm;
  GdkGC* gc;
  ScmObj x1__scm;
  int x1_;
  ScmObj y1__scm;
  int y1_;
  ScmObj x2__scm;
  int x2_;
  ScmObj y2__scm;
  int y2_;
  ScmObj SCM_SUBRARGS[6];
  int SCM_i;
  SCM_ENTER_SUBR("gdk-draw-line");
  for (SCM_i=0; SCM_i<6; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  drawable_scm = SCM_SUBRARGS[0];
  if (!SCM_GDK_DRAWABLE_P(drawable_scm)) Scm_Error("<gdk-drawable> required, but got %S", drawable_scm);
  drawable = SCM_GDK_DRAWABLE(drawable_scm);
  gc_scm = SCM_SUBRARGS[1];
  if (!SCM_GDK_GC_P(gc_scm)) Scm_Error("<gdk-gc> required, but got %S", gc_scm);
  gc = SCM_GDK_GC(gc_scm);
  x1__scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(x1__scm)) Scm_Error("C integer required, but got %S", x1__scm);
  x1_ = Scm_GetInteger(x1__scm);
  y1__scm = SCM_SUBRARGS[3];
  if (!SCM_INTEGERP(y1__scm)) Scm_Error("C integer required, but got %S", y1__scm);
  y1_ = Scm_GetInteger(y1__scm);
  x2__scm = SCM_SUBRARGS[4];
  if (!SCM_INTEGERP(x2__scm)) Scm_Error("C integer required, but got %S", x2__scm);
  x2_ = Scm_GetInteger(x2__scm);
  y2__scm = SCM_SUBRARGS[5];
  if (!SCM_INTEGERP(y2__scm)) Scm_Error("C integer required, but got %S", y2__scm);
  y2_ = Scm_GetInteger(y2__scm);
  {
gdk_draw_line(drawable, gc, x1_, y1_, x2_, y2_);
SCM_RETURN(SCM_UNDEFINED);
  }
}
