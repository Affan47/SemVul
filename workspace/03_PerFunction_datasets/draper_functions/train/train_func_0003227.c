tp_base_client_is_handling_channel (TpBaseClient *self,
    TpChannel *channel)
{
  GList *channels, *l;
  gboolean found = FALSE;

  g_return_val_if_fail (TP_IS_BASE_CLIENT (self), FALSE);
  g_return_val_if_fail (self->priv->flags & CLIENT_IS_HANDLER, FALSE);

  channels = tp_base_client_dup_handled_channels (self);
  for (l = channels; l != NULL && !found; l = g_list_next (l))
    {
      TpChannel *chan = l->data;

      if (!tp_strdiff (tp_proxy_get_object_path (channel),
            tp_proxy_get_object_path (chan)))
        found = TRUE;
    }

  g_list_free_full (channels, g_object_unref);
  return found;
}
