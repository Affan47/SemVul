refresh_updates (CcInfoPanel *self)
{
  self->priv->updates_state = CHECKING_UPDATES;
  refresh_update_button (self);

  g_assert (self->priv->pk_proxy != NULL);
  g_dbus_proxy_call (self->priv->pk_proxy,
                     "CreateTransaction",
                     NULL,
                     G_DBUS_CALL_FLAGS_NONE,
                     -1,
                     NULL,
                     (GAsyncReadyCallback) on_pk_get_tid_ready,
                     self);
}
