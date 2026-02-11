gd_tagged_entry_tag_set_label (GdTaggedEntryTag *tag,
                               const gchar *label)
{
  GdTaggedEntryTagPrivate *priv;

  g_return_if_fail (GD_IS_TAGGED_ENTRY_TAG (tag));

  priv = tag->priv;

  if (g_strcmp0 (priv->label, label) != 0)
    {
      GtkWidget *entry;

      g_free (priv->label);
      priv->label = g_strdup (label);
      g_clear_object (&priv->layout);

      entry = GTK_WIDGET (tag->priv->entry);
      if (entry)
        gtk_widget_queue_resize (entry);
    }
}
