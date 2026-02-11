request_token_cb (RestProxyCall *call,
                  const GError  *error,
                  GObject       *weak_object,
                  gpointer       user_data)
{
  AuthData *data = user_data;
  OAuthProxy *proxy = NULL;

  g_object_get (call, "proxy", &proxy, NULL);
  g_assert (proxy);

  if (!error) {
    oauth_proxy_call_parse_token_reponse (OAUTH_PROXY_CALL (call));
  }

  data->callback (proxy, error, weak_object, data->user_data);

  g_slice_free (AuthData, data);
  g_object_unref (call);
  g_object_unref (proxy);
}
