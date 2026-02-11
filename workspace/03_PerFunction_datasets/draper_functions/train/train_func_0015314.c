introspect_self_handle (TpConnection *self)
{
  if (!self->priv->introspecting_after_connected)
    {
      tp_connection_continue_introspection (self);
      return;
    }

  g_assert (self->priv->introspection_call == NULL);
  self->priv->introspection_call = tp_cli_connection_call_get_self_handle (
      self, -1, got_self_handle, NULL, NULL, NULL);
}
