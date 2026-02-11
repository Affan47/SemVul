invalidated_cb (TpFileTransferChannel *self,
    guint domain,
    gint code,
    gchar *message,
    gpointer user_data)
{

  if (self->priv->cancellable != NULL)
    g_cancellable_cancel (self->priv->cancellable);
}
