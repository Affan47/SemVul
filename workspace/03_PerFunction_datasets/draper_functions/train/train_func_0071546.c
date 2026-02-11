tp_base_client_add_handler_capabilities_varargs (TpBaseClient *self,
    const gchar *first_token, ...)
{
  va_list ap;
  const gchar *token;

  g_return_if_fail (TP_IS_BASE_CLIENT (self));
  g_return_if_fail (!self->priv->registered);

  va_start (ap, first_token);

  for (token = first_token; token != NULL; token = va_arg (ap, gchar *))
    _tp_base_client_add_handler_capability (self, token);

  va_end (ap);
}
