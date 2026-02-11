g_tls_file_database_gnutls_lookup_certificate_issuer (GTlsDatabase           *database,
                                                      GTlsCertificate        *certificate,
                                                      GTlsInteraction        *interaction,
                                                      GTlsDatabaseLookupFlags flags,
                                                      GCancellable           *cancellable,
                                                      GError                **error)
{
  GTlsFileDatabaseGnutls *self = G_TLS_FILE_DATABASE_GNUTLS (database);
  gnutls_datum_t dn = { NULL, 0 };
  GBytes *subject, *der;
  gnutls_datum_t datum;
  GTlsCertificate *issuer = NULL;
  gnutls_x509_crt_t cert;
  gsize length;
  int gerr;

  g_return_val_if_fail (G_IS_TLS_CERTIFICATE_GNUTLS (certificate), NULL);

  if (g_cancellable_set_error_if_cancelled (cancellable, error))
    return NULL;

  if (flags & G_TLS_DATABASE_LOOKUP_KEYPAIR)
    return NULL;


  cert = g_tls_certificate_gnutls_get_cert (G_TLS_CERTIFICATE_GNUTLS (certificate));
  gerr = gnutls_x509_crt_get_raw_issuer_dn (cert, &dn);
  if (gerr < 0)
    {
      g_warning ("failed to get issuer of certificate: %s", gnutls_strerror (gerr));
      return NULL;
    }

  subject = g_bytes_new_with_free_func (dn.data, dn.size, gnutls_free, dn.data);


  g_mutex_lock (&self->priv->mutex);
  der = bytes_multi_table_lookup_ref_one (self->priv->subjects, subject);
  g_mutex_unlock (&self->priv->mutex);

  g_bytes_unref (subject);

  if (g_cancellable_set_error_if_cancelled (cancellable, error))
    {
      issuer = NULL;
    }
  else if (der != NULL)
    {
      datum.data = (unsigned char *)g_bytes_get_data (der, &length);
      datum.size = length;
      issuer = g_tls_certificate_gnutls_new (&datum, NULL);
    }

  if (der != NULL)
    g_bytes_unref (der);
  return issuer;
}
