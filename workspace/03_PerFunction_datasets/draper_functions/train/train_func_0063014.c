content_added_cb (TpChannel *channel,
    const gchar *object_path,
    gpointer user_data,
    GObject *weak_object)
{
  TpCallChannel *self = (TpCallChannel *) channel;

  if (!self->priv->properties_retrieved)
    return;

  ensure_content (self, object_path);
}
