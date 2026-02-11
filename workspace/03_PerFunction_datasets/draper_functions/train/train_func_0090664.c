tp_account_set_service_async (TpAccount *self,
    const char *service,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  GSimpleAsyncResult *result;
  GValue value = {0, };

  g_return_if_fail (TP_IS_ACCOUNT (self));

  if (service == NULL)
    service = "";

  result = g_simple_async_result_new (G_OBJECT (self), callback,
      user_data, tp_account_set_service_async);

  g_value_init (&value, G_TYPE_STRING);
  g_value_set_string (&value, service);

  tp_cli_dbus_properties_call_set (self, -1, TP_IFACE_ACCOUNT,
      "Service", &value, _tp_account_property_set_cb, result, NULL,
      G_OBJECT (self));

  g_value_unset (&value);
}
