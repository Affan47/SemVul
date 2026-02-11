g_tls_certificate_gnutls_get_property (GObject    *object,
				       guint       prop_id,
				       GValue     *value,
				       GParamSpec *pspec)
{
  GTlsCertificateGnutls *gnutls = G_TLS_CERTIFICATE_GNUTLS (object);
  GByteArray *certificate;
  char *certificate_pem;
  int status;
  size_t size;

  switch (prop_id)
    {
    case PROP_CERTIFICATE:
      size = 0;
      status = gnutls_x509_crt_export (gnutls->priv->cert,
				       GNUTLS_X509_FMT_DER,
				       NULL, &size);
      if (status != GNUTLS_E_SHORT_MEMORY_BUFFER)
	certificate = NULL;
      else
	{
	  certificate = g_byte_array_sized_new (size);
	  certificate->len = size;
	  status = gnutls_x509_crt_export (gnutls->priv->cert,
					   GNUTLS_X509_FMT_DER,
					   certificate->data, &size);
	  if (status != 0)
	    {
	      g_byte_array_free (certificate, TRUE);
	      certificate = NULL;
	    }
	}
      g_value_take_boxed (value, certificate);
      break;

    case PROP_CERTIFICATE_PEM:
      size = 0;
      status = gnutls_x509_crt_export (gnutls->priv->cert,
				       GNUTLS_X509_FMT_PEM,
				       NULL, &size);
      if (status != GNUTLS_E_SHORT_MEMORY_BUFFER)
	certificate_pem = NULL;
      else
	{
	  certificate_pem = g_malloc (size);
	  status = gnutls_x509_crt_export (gnutls->priv->cert,
					   GNUTLS_X509_FMT_PEM,
					   certificate_pem, &size);
	  if (status != 0)
	    {
	      g_free (certificate_pem);
	      certificate_pem = NULL;
	    }
	}
      g_value_take_string (value, certificate_pem);
      break;

    case PROP_ISSUER:
      g_value_set_object (value, gnutls->priv->issuer);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}
