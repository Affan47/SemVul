evd_daemon_set_timeout (EvdDaemon   *self,
                        guint        timeout,
                        GSourceFunc  function,
                        gpointer     user_data)
{
  g_return_val_if_fail (EVD_IS_DAEMON (self), 0);

  return evd_timeout_add (g_main_loop_get_context (self->priv->main_loop),
                          timeout,
                          G_PRIORITY_DEFAULT,
                          function,
                          user_data);
}
