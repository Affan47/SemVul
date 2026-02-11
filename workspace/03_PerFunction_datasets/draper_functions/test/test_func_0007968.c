mock_tls_certificate_finalize (GObject *object)
{
  MockTLSCertificate *self = MOCK_TLS_CERTIFICATE (object);

  tp_clear_boxed (TP_ARRAY_TYPE_TLS_CERTIFICATE_REJECTION_LIST,
      &self->rejections);
  g_free (self->cert_type);
  self->cert_type = NULL;
  g_ptr_array_unref (self->cert_data);
  self->cert_data = NULL;

  G_OBJECT_CLASS (mock_tls_certificate_parent_class)->finalize (object);
}
