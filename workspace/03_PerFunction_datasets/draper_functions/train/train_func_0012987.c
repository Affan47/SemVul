glade_project_has_object (GladeProject *project, GObject *object)
{
  GladeWidget *gwidget;

  g_return_val_if_fail (GLADE_IS_PROJECT (project), FALSE);
  g_return_val_if_fail (G_IS_OBJECT (object), FALSE);

  gwidget = glade_widget_get_from_gobject (object);

  g_return_val_if_fail (GLADE_IS_WIDGET (gwidget), FALSE);

  return glade_project_has_gwidget (project, gwidget);
}
