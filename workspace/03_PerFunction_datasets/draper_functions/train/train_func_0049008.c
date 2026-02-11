glade_project_get_widget_by_name (GladeProject *project,
                                  const gchar  *name)
{
  GList *list;

  g_return_val_if_fail (GLADE_IS_PROJECT (project), NULL);
  g_return_val_if_fail (name != NULL, NULL);

  for (list = project->priv->objects; list; list = list->next)
    {
      GladeWidget *widget;

      widget = glade_widget_get_from_gobject (list->data);

      if (strcmp (glade_widget_get_name (widget), name) == 0)
        return widget;
    }

  return NULL;
}
