tp_tls_certificate_accept_async (TpTLSCertificate *self,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  GSimpleAsyncResult *accept_result;

  g_assert (TP_IS_TLS_CERTIFICATE (self));

  DEBUG ("Accepting TLS certificate");

  accept_result = g_simple_async_result_new (G_OBJECT (self),
      callback, user_data, tp_tls_certificate_accept_async);

  tp_cli_authentication_tls_certificate_call_accept (self,
      -1, cert_proxy_accept_cb,
      accept_result, g_object_unref, NULL);
}
