tp_connection_connection_error_cb (TpConnection *self,
                                   const gchar *error_name,
                                   GHashTable *details,
                                   gpointer user_data,
                                   GObject *weak_object)
{
  g_free (self->priv->connection_error);
  self->priv->connection_error = g_strdup (error_name);

  if (self->priv->connection_error_details != NULL)
    g_hash_table_unref (self->priv->connection_error_details);

  self->priv->connection_error_details = g_boxed_copy (
      TP_HASH_TYPE_STRING_VARIANT_MAP, details);
}
