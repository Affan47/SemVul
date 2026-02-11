inf_gtk_certificate_view_set_certificate(InfGtkCertificateView* view,
                                         gnutls_x509_crt_t cert)
{
  InfGtkCertificateViewPrivate* priv;
  gchar* value;

  g_return_if_fail(INF_GTK_IS_CERTIFICATE_VIEW(view));

  priv = INF_GTK_CERTIFICATE_VIEW_PRIVATE(view);
  priv->certificate = cert;

  if(cert == NULL)
  {
    gtk_label_set_text(GTK_LABEL(priv->common_name), NULL);
    gtk_label_set_text(GTK_LABEL(priv->organization), NULL);
    gtk_label_set_text(GTK_LABEL(priv->organizational_unit), NULL);
    gtk_label_set_text(GTK_LABEL(priv->serial_number), NULL);

    gtk_label_set_text(GTK_LABEL(priv->issuer_common_name), NULL);
    gtk_label_set_text(GTK_LABEL(priv->issuer_organization), NULL);
    gtk_label_set_text(GTK_LABEL(priv->issuer_organizational_unit), NULL);

    gtk_label_set_text(GTK_LABEL(priv->activation_time), NULL);
    gtk_label_set_text(GTK_LABEL(priv->expiration_time), NULL);

    gtk_label_set_text(GTK_LABEL(priv->sha1_fingerprint), NULL);
    gtk_label_set_text(GTK_LABEL(priv->md5_fingerprint), NULL);
  }
  else
  {
    inf_gtk_certificate_view_set_label_dn_by_oid(
      cert,
      GTK_LABEL(priv->common_name),
      GNUTLS_OID_X520_COMMON_NAME
    );

    inf_gtk_certificate_view_set_label_dn_by_oid(
      cert,
      GTK_LABEL(priv->organization),
      GNUTLS_OID_X520_ORGANIZATION_NAME
    );

    inf_gtk_certificate_view_set_label_dn_by_oid(
      cert,
      GTK_LABEL(priv->organizational_unit),
      GNUTLS_OID_X520_ORGANIZATIONAL_UNIT_NAME
    );

    value = inf_cert_util_get_serial_number(cert);
    inf_gtk_certificate_view_set_label(
      GTK_LABEL(priv->serial_number),
      value
    );
    g_free(value);

    inf_gtk_certificate_view_set_label_issuer_dn_by_oid(
      cert,
      GTK_LABEL(priv->issuer_common_name),
      GNUTLS_OID_X520_COMMON_NAME
    );

    inf_gtk_certificate_view_set_label_issuer_dn_by_oid(
      cert,
      GTK_LABEL(priv->issuer_organization),
      GNUTLS_OID_X520_ORGANIZATION_NAME
    );

    inf_gtk_certificate_view_set_label_issuer_dn_by_oid(
      cert,
      GTK_LABEL(priv->issuer_organizational_unit),
      GNUTLS_OID_X520_ORGANIZATIONAL_UNIT_NAME
    );

    value = inf_cert_util_get_activation_time(cert);
    inf_gtk_certificate_view_set_label(
      GTK_LABEL(priv->activation_time),
      value
    );
    g_free(value);

    value = inf_cert_util_get_expiration_time(cert);
    inf_gtk_certificate_view_set_label(
      GTK_LABEL(priv->expiration_time),
      value
    );
    g_free(value);

    value = inf_cert_util_get_fingerprint(cert, GNUTLS_DIG_SHA1);
    inf_gtk_certificate_view_set_label(
      GTK_LABEL(priv->sha1_fingerprint),
      value
    );
    g_free(value);

    value = inf_cert_util_get_fingerprint(cert, GNUTLS_DIG_MD5);
    inf_gtk_certificate_view_set_label(
      GTK_LABEL(priv->md5_fingerprint),
      value
    );
    g_free(value);
  }

  g_object_notify(G_OBJECT(view), "certificate");
}
