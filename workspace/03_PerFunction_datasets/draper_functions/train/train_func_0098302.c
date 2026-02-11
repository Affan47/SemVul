finish_handshake (GTlsConnectionGnutls  *gnutls,
		  GTask                 *task,
		  GError               **error)
{
  GTlsCertificate *peer_certificate;
  GTlsCertificateFlags peer_certificate_errors;

  g_assert (error != NULL);

  peer_certificate = gnutls->priv->peer_certificate_tmp;
  gnutls->priv->peer_certificate_tmp = NULL;
  peer_certificate_errors = gnutls->priv->peer_certificate_errors_tmp;
  gnutls->priv->peer_certificate_errors_tmp = 0;

  if (g_task_propagate_boolean (task, error) && peer_certificate)
    {
      if (!accept_peer_certificate (gnutls, peer_certificate,
				    peer_certificate_errors))
	{
	  g_set_error_literal (error, G_TLS_ERROR, G_TLS_ERROR_BAD_CERTIFICATE,
			       _("Unacceptable TLS certificate"));
	}

      gnutls->priv->peer_certificate = peer_certificate;
      gnutls->priv->peer_certificate_errors = peer_certificate_errors;
      g_object_notify (G_OBJECT (gnutls), "peer-certificate");
      g_object_notify (G_OBJECT (gnutls), "peer-certificate-errors");
    }

  if (*error && gnutls->priv->started_handshake)
    gnutls->priv->handshake_error = g_error_copy (*error);

  return (*error == NULL);
}
