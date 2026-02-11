evd_jsonrpc_transport_receive (EvdJsonrpc    *self,
                               const gchar   *message,
                               gpointer       context,
                               guint          invocation_id,
                               GError       **error)
{
  gsize size;
  GError *_error = NULL;
  gboolean result = TRUE;

  g_return_val_if_fail (EVD_IS_JSONRPC (self), FALSE);

  size = strlen (message);

  if (message == NULL || size == 0)
    return TRUE;

  self->priv->context = context;

  if (! evd_json_filter_feed_len (self->priv->json_filter,
                                  message,
                                  size,
                                  &_error))
    {
      evd_jsonrpc_transport_error (self, invocation_id, _error);
      g_propagate_error (error, _error);

      result = FALSE;
    }

  self->priv->context = NULL;

  return result;
}
