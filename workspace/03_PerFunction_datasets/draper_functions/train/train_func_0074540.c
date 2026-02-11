gd_tagged_entry_map (GtkWidget *widget)
{
  GdTaggedEntry *self = GD_TAGGED_ENTRY (widget);
  GdTaggedEntryTag *tag;
  GList *l;

  if (gtk_widget_get_realized (widget) && !gtk_widget_get_mapped (widget))
    {
      GTK_WIDGET_CLASS (gd_tagged_entry_parent_class)->map (widget);

      for (l = self->priv->tags; l != NULL; l = l->next)
        {
          tag = l->data;
          gdk_window_show (tag->priv->window);
        }
    }
}
