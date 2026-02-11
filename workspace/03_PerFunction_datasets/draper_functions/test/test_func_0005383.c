gtkstyle_gtk_paint_resize_grip(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
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
  ScmObj edge_scm;
  int edge;
  ScmObj x_scm;
  int x;
  ScmObj y_scm;
  int y;
  ScmObj width_scm;
  int width;
  ScmObj height_scm;
  int height;
  ScmObj SCM_SUBRARGS[11];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-paint-resize-grip");
  for (SCM_i=0; SCM_i<11; SCM_i++) {
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
  edge_scm = SCM_SUBRARGS[6];
  if (!SCM_INTEGERP(edge_scm)) Scm_Error("C integer required, but got %S", edge_scm);
  edge = Scm_GetInteger(edge_scm);
  x_scm = SCM_SUBRARGS[7];
  if (!SCM_INTEGERP(x_scm)) Scm_Error("C integer required, but got %S", x_scm);
  x = Scm_GetInteger(x_scm);
  y_scm = SCM_SUBRARGS[8];
  if (!SCM_INTEGERP(y_scm)) Scm_Error("C integer required, but got %S", y_scm);
  y = Scm_GetInteger(y_scm);
  width_scm = SCM_SUBRARGS[9];
  if (!SCM_INTEGERP(width_scm)) Scm_Error("C integer required, but got %S", width_scm);
  width = Scm_GetInteger(width_scm);
  height_scm = SCM_SUBRARGS[10];
  if (!SCM_INTEGERP(height_scm)) Scm_Error("C integer required, but got %S", height_scm);
  height = Scm_GetInteger(height_scm);
  {
gtk_paint_resize_grip(style, window, state_type, area, widget, detail, edge, x, y, width, height);
SCM_RETURN(SCM_UNDEFINED);
  }
}
