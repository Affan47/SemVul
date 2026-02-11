conn_requests_get_requestables (TpBaseConnection *self)
{
  TpBaseConnectionPrivate *priv = self->priv;

  GPtrArray *details = g_ptr_array_sized_new (priv->channel_managers->len * 2);
  guint i;

  for (i = 0; i < priv->channel_managers->len; i++)
    {
      TpChannelManager *manager = TP_CHANNEL_MANAGER (
          g_ptr_array_index (priv->channel_managers, i));

      tp_channel_manager_foreach_channel_class (manager,
          get_requestables_foreach, details);
    }

  return details;
}
