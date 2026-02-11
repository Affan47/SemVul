evd_json_filter_init (EvdJsonFilter *self)
{
  EvdJsonFilterPrivate *priv;

  priv = EVD_JSON_FILTER_GET_PRIVATE (self);
  self->priv = priv;


  priv->stack = g_new0 (gint, MAX_DEPTH);
  priv->cache = g_string_new ("");

  evd_json_filter_reset (self);

  priv->on_packet = NULL;
}
