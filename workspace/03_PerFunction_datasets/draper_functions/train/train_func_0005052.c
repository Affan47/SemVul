build_certificate_chain (GTlsDatabaseGnutls      *self,
                         GTlsCertificateGnutls   *certificate,
                         GTlsCertificateGnutls   *previous,
                         gboolean                 certificate_is_from_db,
                         guint                    recursion_depth,
                         const gchar             *purpose,
                         GSocketConnectable      *identity,
                         GTlsInteraction         *interaction,
                         GCancellable            *cancellable,
                         GTlsCertificateGnutls  **anchor,
                         GError                 **error)
{
  GTlsCertificate *issuer;
  gint status;

  if (recursion_depth++ > BUILD_CERTIFICATE_CHAIN_RECURSION_LIMIT)
    return STATUS_RECURSION_LIMIT_REACHED;

  if (g_cancellable_set_error_if_cancelled (cancellable, error))
    return STATUS_FAILURE;


  if (g_tls_database_gnutls_lookup_assertion (self, certificate,
                                              G_TLS_DATABASE_GNUTLS_ANCHORED_CERTIFICATE,
                                              purpose, identity, cancellable, error))
    {
      g_tls_certificate_gnutls_set_issuer (certificate, NULL);
      *anchor = certificate;
      return STATUS_ANCHORED;
    }
  else if (*error)
    {
      return STATUS_FAILURE;
    }


  if (is_self_signed (certificate))
    {


      if (previous && !certificate_is_from_db)
        {
          issuer = g_tls_database_lookup_certificate_issuer (G_TLS_DATABASE (self),
                                                             G_TLS_CERTIFICATE (previous),
                                                             interaction,
                                                             G_TLS_DATABASE_LOOKUP_NONE,
                                                             cancellable, error);
          if (*error)
            {
              return STATUS_FAILURE;
            }
          else if (issuer)
            {

              g_return_val_if_fail (G_IS_TLS_CERTIFICATE_GNUTLS (issuer), STATUS_FAILURE);
              certificate = G_TLS_CERTIFICATE_GNUTLS (issuer);
              g_tls_certificate_gnutls_set_issuer (previous, certificate);
              g_object_unref (issuer);

              return build_certificate_chain (self, certificate, previous, TRUE, recursion_depth,
                                              purpose, identity, interaction, cancellable, anchor, error);
            }
        }

      g_tls_certificate_gnutls_set_issuer (certificate, NULL);
      return STATUS_SELFSIGNED;
    }

  previous = certificate;


  issuer = g_tls_certificate_get_issuer (G_TLS_CERTIFICATE (certificate));
  if (issuer)
    {
      g_return_val_if_fail (G_IS_TLS_CERTIFICATE_GNUTLS (issuer), STATUS_FAILURE);
      certificate = G_TLS_CERTIFICATE_GNUTLS (issuer);

      status = build_certificate_chain (self, certificate, previous, FALSE, recursion_depth,
                                        purpose, identity, interaction, cancellable, anchor, error);
      if (status != STATUS_INCOMPLETE)
        {
          return status;
        }
    }


  issuer = g_tls_database_lookup_certificate_issuer (G_TLS_DATABASE (self),
                                                     G_TLS_CERTIFICATE (certificate),
                                                     interaction,
                                                     G_TLS_DATABASE_LOOKUP_NONE,
                                                     cancellable, error);
  if (*error)
    return STATUS_FAILURE;

  if (!issuer)
    return STATUS_INCOMPLETE;

  g_return_val_if_fail (G_IS_TLS_CERTIFICATE_GNUTLS (issuer), STATUS_FAILURE);
  g_tls_certificate_gnutls_set_issuer (certificate, G_TLS_CERTIFICATE_GNUTLS (issuer));
  certificate = G_TLS_CERTIFICATE_GNUTLS (issuer);
  g_object_unref (issuer);

  return build_certificate_chain (self, certificate, previous, TRUE, recursion_depth,
                                  purpose, identity, interaction, cancellable, anchor, error);
}
