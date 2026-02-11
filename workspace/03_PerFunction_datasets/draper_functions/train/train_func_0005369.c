authenticate (RestProxy   *self,
              SoupMessage *msg,
              SoupAuth    *soup_auth,
              gboolean     retrying,
              SoupSession *session)
{
  RestProxyPrivate *priv = GET_PRIVATE (self);
  RestProxyAuth *rest_auth;
  gboolean try_auth;

  rest_auth = rest_proxy_auth_new (self, session, msg, soup_auth);
  g_signal_emit(self, signals[AUTHENTICATE], 0, rest_auth, retrying, &try_auth);
  if (try_auth && !rest_proxy_auth_is_paused (rest_auth))
    soup_auth_authenticate (soup_auth, priv->username, priv->password);
  g_object_unref (G_OBJECT (rest_auth));
}
