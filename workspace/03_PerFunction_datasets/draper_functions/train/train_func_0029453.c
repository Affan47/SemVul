glade_gtk_grid_parse_finished (GladeProject *project, GObject *container)
{
  GladeWidget *gwidget = glade_widget_get_from_gobject (container);
  GladeGridAttachments attach;
  GList *list, *children;
  gint row = 0, column = 0, n_row = 0, n_column = 0;

  children = gtk_container_get_children (GTK_CONTAINER (container));

  for (list = children; list; list = list->next)
    {
      GtkWidget *widget = list->data;

      if (GLADE_IS_PLACEHOLDER (widget)) continue;

      glade_gtk_grid_get_child_attachments (GTK_WIDGET (container), widget, &attach);

      n_row = attach.top_attach + attach.height;
      n_column = attach.left_attach + attach.width;

      if (row < n_row) row = n_row;
      if (column < n_column) column = n_column;
    }

  if (column) glade_widget_property_set (gwidget, "n-columns", column);
  if (row) glade_widget_property_set (gwidget, "n-rows", row);

  g_list_free (children);


  glade_gtk_grid_refresh_placeholders (GTK_GRID (container), TRUE);
}
