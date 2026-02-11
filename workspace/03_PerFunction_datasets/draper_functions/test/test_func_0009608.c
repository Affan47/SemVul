gtktreeviewcolumn_gtk_cell_set_color(ScmObj *SCM_FP, int SCM_ARGCNT, void *data_)
{
  ScmObj cell_renderer_scm;
  GtkCellRenderer* cell_renderer;
  ScmObj property_scm;
  const gchar * property;
  ScmObj color_scm;
  GdkColor* color;
  ScmObj SCM_SUBRARGS[3];
  int SCM_i;
  SCM_ENTER_SUBR("gtk-cell-set-color");
  for (SCM_i=0; SCM_i<3; SCM_i++) {
    SCM_SUBRARGS[SCM_i] = SCM_ARGREF(SCM_i);
  }
  cell_renderer_scm = SCM_SUBRARGS[0];
  if (!SCM_GTK_CELL_RENDERER_P(cell_renderer_scm)) Scm_Error("<gtk-cell-renderer> required, but got %S", cell_renderer_scm);
  cell_renderer = SCM_GTK_CELL_RENDERER(cell_renderer_scm);
  property_scm = SCM_SUBRARGS[1];
  if (!SCM_STRINGP(property_scm)) Scm_Error("<const-gchar*> required, but got %S", property_scm);
  property = CONST_GCHAR_PTR(property_scm);
  color_scm = SCM_SUBRARGS[2];
  if (!SCM_GDK_COLOR_P(color_scm)) Scm_Error("<gdk-color> required, but got %S", color_scm);
  color = SCM_GDK_COLOR(color_scm);
  {
g_object_set(cell_renderer, property, color, NULL);
SCM_RETURN(SCM_UNDEFINED);
  }
}
