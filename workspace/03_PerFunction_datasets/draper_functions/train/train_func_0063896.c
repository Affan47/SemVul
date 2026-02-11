online_notify (gboolean online, gpointer user_data)
{
  SwServicePlurk *plurk = (SwServicePlurk *)user_data;
  SwServicePlurkPrivate *priv = GET_PRIVATE (plurk);

  priv->credentials = OFFLINE;

  if (online) {
    if (priv->username && priv->password) {
      RestProxyCall *call;

      call = rest_proxy_new_call (priv->proxy);
      rest_proxy_call_set_function (call, "Users/login");
      rest_proxy_call_add_params (call,
                                  "api_key", priv->api_key,
                                  "username", priv->username,
                                  "password", priv->password,
                                  NULL);
      rest_proxy_call_async (call, _got_login_data, (GObject*)plurk, NULL, NULL);
    }
  } else {
    g_free (priv->user_id);
    priv->user_id = NULL;

    sw_service_emit_capabilities_changed ((SwService *)plurk,
                                          get_dynamic_caps ((SwService *)plurk));
  }
}
