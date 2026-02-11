tp_tls_certificate_finalize (GObject *object)
{
  TpTLSCertificate *self = TP_TLS_CERTIFICATE (object);
  TpTLSCertificatePrivate *priv = self->priv;

  DEBUG ("%p", object);

  tp_clear_pointer (&self->priv->rejections, g_ptr_array_unref);
  g_free (priv->cert_type);
  if (priv->cert_data != NULL)
    g_ptr_array_unref (priv->cert_data);
  tp_clear_boxed (TP_ARRAY_TYPE_TLS_CERTIFICATE_REJECTION_LIST,
      &self->priv->pending_rejections);

  G_OBJECT_CLASS (tp_tls_certificate_parent_class)->finalize (object);
}
