g_tls_connection_gnutls_set_handshake_priority (GTlsConnectionGnutls *gnutls)
{
  gboolean use_ssl3, unsafe_rehandshake;

  if (G_IS_TLS_CLIENT_CONNECTION (gnutls))
    use_ssl3 = g_tls_client_connection_get_use_ssl3 (G_TLS_CLIENT_CONNECTION (gnutls));
  else
    use_ssl3 = FALSE;
  unsafe_rehandshake = (gnutls->priv->rehandshake_mode == G_TLS_REHANDSHAKE_UNSAFELY);
  gnutls_priority_set (gnutls->priv->session,
		       priorities[use_ssl3][unsafe_rehandshake]);
}
