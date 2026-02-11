got_enabled_cb (
    TpProxy *proxy,
    const GValue *value,
    const GError *error,
    gpointer user_data,
    GObject *weak_object)
{
  TpDebugClient *self = TP_DEBUG_CLIENT (proxy);

  if (error != NULL)
    {
      tp_proxy_invalidate (proxy, error);
    }
  else if (!G_VALUE_HOLDS_BOOLEAN (value))
    {
      GError *e = g_error_new (TP_ERROR,
          TP_ERROR_NOT_IMPLEMENTED,
          "this service doesn't implement the Debug interface correctly "
          "(the Enabled property is not a boolean, but a %s)",
          G_VALUE_TYPE_NAME (value));

      tp_proxy_invalidate (proxy, e);
      g_error_free (e);
    }
  else
    {
      self->priv->enabled = g_value_get_boolean (value);

      _tp_proxy_set_feature_prepared (proxy, TP_DEBUG_CLIENT_FEATURE_CORE,
          TRUE);
    }
}
