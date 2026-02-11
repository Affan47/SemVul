gtkstyle_gtk_paint_vline(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj style_scm;
  GtkStyle* style;
  ScmObj window_scm;
  GdkDrawable* window;
  ScmObj state_type_scm;
  int state_type;
  ScmObj area_scm;
  GdkRectangle* area;
  ScmObj widget_scm;
  GtkWidget* widget;
  ScmObj detail_scm;
  const gchar * detail;
  ScmObj y1__scm;
  int y1_;
  ScmObj y2__scm;
  int y2_;
  ScmObj x_scm;
  int x;
  ScmObj SCM_SUBRARGS[9];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-paint-vline");
  for (SCM_i=0; SCM_i<9; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  style_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_STYLE_P(style_scm)) Scm_Error("<gtk-style> required, but got %S", style_scm);
  style = SCM_GTK_STYLE(style_scm);
  window_scm = SCM_SUBRARGS[1];
  if (!SCM_GDK_DRAWABLE_P(window_scm)) Scm_Error("<gdk-drawable> required, but got %S", window_scm);
  window = SCM_GDK_DRAWABLE(window_scm);
  state_type_scm = SCM_SUBRARGS[2];
  if (!SCM_INTEGERP(state_type_scm)) Scm_Error("C integer required, but got %S", state_type_scm);
  state_type = Scm_GetInteger(state_type_scm);
  area_scm = SCM_SUBRARGS[3];
  if (!SCM_GDK_RECTANGLE_P(area_scm)) Scm_Error("<gdk-rectangle> required, but got %S", area_scm);
  area = SCM_GDK_RECTANGLE(area_scm);
  widget_scm = SCM_SUBRARGS[4];
  if (!SCM_GTK_WIDGET_P(widget_scm)) Scm_Error("<gtk-widget> required, but got %S", widget_scm);
  widget = SCM_GTK_WIDGET(widget_scm);
  detail_scm = SCM_SUBRARGS[5];
  if (!SCM_STRINGP(detail_scm)) Scm_Error("<const-gchar*> required, but got %S", detail_scm);
  detail = CONST_GCHAR_PTR(detail_scm);
  y1__scm = SCM_SUBRARGS[6];
  if (!SCM_INTEGERP(y1__scm)) Scm_Error("C integer required, but got %S", y1__scm);
  y1_ = Scm_GetInteger(y1__scm);
  y2__scm = SCM_SUBRARGS[7];
  if (!SCM_INTEGERP(y2__scm)) Scm_Error("C integer required, but got %S", y2__scm);
  y2_ = Scm_GetInteger(y2__scm);
  x_scm = SCM_SUBRARGS[8];
  if (!SCM_INTEGERP(x_scm)) Scm_Error("C integer required, but got %S", x_scm);
  x = Scm_GetInteger(x_scm);
  {
gtk_paint_vline(style, window, state_type, area, widget, detail, y1_, y2_, x);
SCM_RETURN(SCM_UNDEFINED);
  }
}
