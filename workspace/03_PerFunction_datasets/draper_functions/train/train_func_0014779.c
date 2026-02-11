restore_all_children (GladeWidget *widget)
{
  GList *children, *l;

  children = glade_widget_get_children (widget);

  for (l = children; l; l = l->next)
    {
      GtkWidget *child = l->data;

      restore_expand_data (child);
    }
}
