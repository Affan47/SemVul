tp_contact_search_start (TpContactSearch *self,
    GHashTable *criteria)
{
  g_return_if_fail (TP_IS_CONTACT_SEARCH (self));
  g_return_if_fail (TP_IS_CHANNEL (self->priv->channel));
  g_return_if_fail (self->priv->state ==
      TP_CHANNEL_CONTACT_SEARCH_STATE_NOT_STARTED);

  tp_cli_channel_type_contact_search_call_search (self->priv->channel,
      -1, criteria, NULL, NULL, NULL, NULL);
}
