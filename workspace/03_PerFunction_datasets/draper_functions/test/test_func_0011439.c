extract_pem_cert_data (GByteArray *contents, GError **error)
{
	GByteArray *cert = NULL;
	gsize start = 0, end = 0;
	unsigned char *der = NULL;
	guint8 save_end;
	gsize length = 0;

	if (!find_tag (PEM_CERT_BEGIN, contents, 0, &start)) {
		g_set_error (error, NM_CRYPTO_ERROR,
			         NM_CRYPTO_ERR_FILE_FORMAT_INVALID,
			         _("PEM certificate had no start tag '%s'."),
			         PEM_CERT_BEGIN);
		goto done;
	}

	start += strlen (PEM_CERT_BEGIN);
	if (!find_tag (PEM_CERT_END, contents, start, &end)) {
		g_set_error (error, NM_CRYPTO_ERROR,
			         NM_CRYPTO_ERR_FILE_FORMAT_INVALID,
			         _("PEM certificate had no end tag '%s'."),
			         PEM_CERT_END);
		goto done;
	}


	save_end = contents->data[end];
	contents->data[end] = '\0';
	der = g_base64_decode ((const char *) (contents->data + start), &length);
	contents->data[end] = save_end;

	if (der && length) {
		cert = g_byte_array_sized_new (length);
		if (cert) {
			g_byte_array_append (cert, der, length);
			g_assert (cert->len == length);
		} else {
			g_set_error (error, NM_CRYPTO_ERROR,
						 NM_CRYPTO_ERR_OUT_OF_MEMORY,
						 _("Not enough memory to store certificate data."));
		}
	} else {
		g_set_error (error, NM_CRYPTO_ERROR,
			         NM_CRYPTO_ERR_DECODE_FAILED,
			         _("Failed to decode certificate."));
	}

done:
	g_free (der);
	return cert;
}
