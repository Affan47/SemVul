oauth_proxy_request_token_async (OAuthProxy            *proxy,
                                 const char            *function,
                                 const char            *callback_uri,
                                 OAuthProxyAuthCallback callback,
                                 GObject               *weak_object,
                                 gpointer               user_data,
                                 GError               **error)
{
  RestProxyCall *call;
  AuthData *data;

  call = rest_proxy_new_call (REST_PROXY (proxy));
  rest_proxy_call_set_function (call, function ? function : "request_token");
  rest_proxy_call_set_method (call, "POST");

  if (callback_uri)
    rest_proxy_call_add_param (call, "oauth_callback", callback_uri);

  data = g_slice_new0 (AuthData);
  data->callback = callback;
  data->user_data = user_data;

  return rest_proxy_call_async (call, request_token_cb, weak_object, data, error);
}
