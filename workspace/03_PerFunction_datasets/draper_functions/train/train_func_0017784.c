g_tls_certificate_gnutls_set_data (GTlsCertificateGnutls *gnutls,
                                   const gnutls_datum_t  *datum)
{
  g_return_if_fail (G_IS_TLS_CERTIFICATE_GNUTLS (gnutls));
  g_return_if_fail (!gnutls->priv->have_cert);

  if (gnutls_x509_crt_import (gnutls->priv->cert, datum,
                              GNUTLS_X509_FMT_DER) == 0)
    gnutls->priv->have_cert = TRUE;
}
