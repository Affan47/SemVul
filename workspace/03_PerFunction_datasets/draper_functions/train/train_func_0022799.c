shell_mime_sniffer_sniff_async (ShellMimeSniffer *self,
                                GAsyncReadyCallback callback,
                                gpointer user_data)
{
  g_assert (self->priv->watchdog_id == 0);
  g_assert (self->priv->async_result == NULL);

  self->priv->async_result =
    g_simple_async_result_new (G_OBJECT (self),
                               callback, user_data,
                               shell_mime_sniffer_sniff_finish);

  self->priv->cancellable = g_cancellable_new ();

  self->priv->watchdog_id =
    g_timeout_add (WATCHDOG_TIMEOUT,
                   watchdog_timeout_reached_cb, self);

  start_loading_file (self);
}
