g_tls_certificate_gnutls_pkcs11_build_certificate_uri (GTlsCertificateGnutlsPkcs11 *self,
                                                       const gchar *interaction_id)
{
  g_return_val_if_fail (G_IS_TLS_CERTIFICATE_GNUTLS_PKCS11 (self), NULL);
  if (self->priv->certificate_uri == NULL)
    return NULL;
  else if (interaction_id)
    return g_strdup_printf ("%s;pinfile=%s", self->priv->certificate_uri, interaction_id);
  else
    return g_strdup (self->priv->certificate_uri);
}
