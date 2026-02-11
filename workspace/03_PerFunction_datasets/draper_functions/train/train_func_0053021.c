rest_proxy_call_sync (RestProxyCall *call,
                      GError       **error_out)
{
  RestProxyCallPrivate *priv;
  SoupMessage *message;
  gboolean ret;

  g_return_val_if_fail (REST_IS_PROXY_CALL (call), FALSE);

  priv = GET_PRIVATE (call);

  message = prepare_message (call, error_out);
  if (!message)
    return FALSE;

  _rest_proxy_send_message (priv->proxy, message);

  ret = finish_call (call, message, error_out);

  g_object_unref (message);

  return ret;
}
