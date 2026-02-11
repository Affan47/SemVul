rest_proxy_auth_pause (RestProxyAuth *auth)
{
  g_return_if_fail (REST_IS_PROXY_AUTH (auth));

  if (auth->priv->paused)
      return;

  auth->priv->paused = TRUE;
  soup_session_pause_message (auth->priv->session, auth->priv->message);
}
