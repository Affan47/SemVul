infc_session_proxy_get_property(GObject* object,
                                guint prop_id,
                                GValue* value,
                                GParamSpec* pspec)
{
  InfcSessionProxy* session;
  InfcSessionProxyPrivate* priv;

  session = INFC_SESSION_PROXY(object);
  priv = INFC_SESSION_PROXY_PRIVATE(session);

  switch(prop_id)
  {
  case PROP_SESSION:
    g_value_set_object(value, G_OBJECT(priv->session));
    break;
  case PROP_SUBSCRIPTION_GROUP:
    g_value_set_boxed(value, priv->subscription_group);
    break;
  case PROP_CONNECTION:
    g_value_set_object(value, G_OBJECT(priv->connection));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}
