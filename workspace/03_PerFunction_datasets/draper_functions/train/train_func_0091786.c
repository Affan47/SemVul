_sina_status_update_update_status (SwStatusUpdateIface   *self,
                                   const gchar           *msg,
                                   GHashTable            *fields,
                                   DBusGMethodInvocation *context)
{
  SwServiceSina *sina = SW_SERVICE_SINA (self);
  SwServiceSinaPrivate *priv = GET_PRIVATE (sina);
  RestProxyCall *call;

  if (!priv->user_id)
    return;

  call = rest_proxy_new_call (priv->proxy);
  rest_proxy_call_set_method (call, "POST");
  rest_proxy_call_set_function (call, "statuses/update.xml");

  rest_proxy_call_add_params (call,
                              "status", msg,
                              NULL);

  rest_proxy_call_async (call, _update_status_cb, (GObject *)self, NULL, NULL);
  sw_status_update_iface_return_from_update_status (context);
}
