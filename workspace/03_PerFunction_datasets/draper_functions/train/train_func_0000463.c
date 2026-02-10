gd_tagged_entry_add_tag (GdTaggedEntry *self,
                         const gchar *id,
                         const gchar *name)
{
  GdTaggedEntryTag *tag;

  if (gd_tagged_entry_find_tag_by_id (self, id) != NULL)
    return FALSE;

  tag = gd_tagged_entry_tag_new (id, name);
  self->priv->tags = g_list_append (self->priv->tags, tag);

  if (gtk_widget_get_mapped (GTK_WIDGET (self)))
    {
      gd_tagged_entry_tag_realize (tag, self);
      gdk_window_show_unraised (tag->window);
    }

  gtk_widget_queue_resize (GTK_WIDGET (self));

  return TRUE;
}
