tp_base_client_delegate_channels_async (TpBaseClient *self,
    GList *channels,
    gint64 user_action_time,
    const gchar *preferred_handler,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  TpChannelDispatcher *cd;
  GSimpleAsyncResult *result;
  DelegateChannelsCtx *ctx;
  GPtrArray *chans;
  GList *l;

  g_return_if_fail (TP_IS_BASE_CLIENT (self));
  g_return_if_fail (self->priv->flags & CLIENT_IS_HANDLER);

  cd = tp_channel_dispatcher_new (self->priv->dbus);

  chans = g_ptr_array_new_full (g_list_length (channels), g_free);

  for (l = channels; l != NULL; l = g_list_next (l))
    {
      TpChannel *channel = l->data;

      g_return_if_fail (TP_IS_CHANNEL (channel));

      g_ptr_array_add (chans, g_strdup (tp_proxy_get_object_path (channel)));
    }

  result = g_simple_async_result_new (G_OBJECT (self), callback, user_data,
      tp_base_client_delegate_channels_async);

  ctx = delegate_channels_ctx_new (channels);

  g_simple_async_result_set_op_res_gpointer (result, ctx,
      (GDestroyNotify) delegate_channels_ctx_free);


  tp_cli_channel_dispatcher_call_delegate_channels (cd, 1000 * 60 * 2,
      chans, user_action_time,
      preferred_handler == NULL ? "" : preferred_handler,
      delegate_channels_cb, result, g_object_unref, G_OBJECT (self));

  g_object_unref (cd);
  g_ptr_array_unref (chans);
}
