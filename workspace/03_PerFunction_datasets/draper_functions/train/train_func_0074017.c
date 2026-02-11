infd_session_proxy_constructor(GType type,
                               guint n_construct_properties,
                               GObjectConstructParam* construct_properties)
{
  GObject* object;
  InfdSessionProxy* session_proxy;
  InfdSessionProxyPrivate* priv;

  object = G_OBJECT_CLASS(parent_class)->constructor(
    type,
    n_construct_properties,
    construct_properties
  );

  session_proxy = INFD_SESSION_PROXY(object);
  priv = INFD_SESSION_PROXY_PRIVATE(session_proxy);

  g_assert(priv->subscription_group != NULL);
  g_assert(priv->session != NULL);


  if(inf_session_get_status(priv->session) == INF_SESSION_SYNCHRONIZING)
    priv->idle = FALSE;


  inf_session_set_subscription_group(
    priv->session,
    INF_COMMUNICATION_GROUP(priv->subscription_group)
  );

  return object;
}
