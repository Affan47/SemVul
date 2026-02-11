smime_context_verify_sync (CamelCipherContext *context,
                           CamelMimePart *ipart,
                           GCancellable *cancellable,
                           GError **error)
{
	CamelCipherContextClass *class;
	NSSCMSDecoderContext *dec;
	NSSCMSMessage *cmsg;
	CamelStream *mem;
	CamelStream *constream = NULL;
	CamelCipherValidity *valid = NULL;
	CamelContentType *ct;
	const gchar *tmp;
	CamelMimePart *sigpart;
	CamelDataWrapper *dw;
	GByteArray *buffer;

	class = CAMEL_CIPHER_CONTEXT_GET_CLASS (context);

	dw = camel_medium_get_content ((CamelMedium *) ipart);
	ct = dw->mime_type;


	buffer = g_byte_array_new ();
	mem = camel_stream_mem_new_with_byte_array (buffer);

	if (camel_content_type_is (ct, "multipart", "signed")) {
		CamelMultipart *mps = (CamelMultipart *) dw;

		tmp = camel_content_type_param (ct, "protocol");
		if (!CAMEL_IS_MULTIPART_SIGNED (mps)
		    || tmp == NULL
		    || (g_ascii_strcasecmp (tmp, class->sign_protocol) != 0
			&& g_ascii_strcasecmp (tmp, "application/pkcs7-signature") != 0)) {
			g_set_error (
				error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
				_("Cannot verify message signature: "
				"Incorrect message format"));
			goto fail;
		}

		constream = camel_multipart_signed_get_content_stream (
			(CamelMultipartSigned *) mps, error);
		if (constream == NULL)
			goto fail;

		sigpart = camel_multipart_get_part (mps, CAMEL_MULTIPART_SIGNED_SIGNATURE);
		if (sigpart == NULL) {
			g_set_error (
				error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
				_("Cannot verify message signature: "
				"Incorrect message format"));
			goto fail;
		}
	} else if (camel_content_type_is (ct, "application", "x-pkcs7-mime")) {
		sigpart = ipart;
	} else {
		g_set_error (
			error, CAMEL_ERROR, CAMEL_ERROR_GENERIC,
			_("Cannot verify message signature: "
			"Incorrect message format"));
		goto fail;
	}

	dec = NSS_CMSDecoder_Start (
		NULL,
		NULL, NULL,
		NULL, NULL,
		NULL, NULL);

	camel_data_wrapper_decode_to_stream_sync (
		camel_medium_get_content (
			CAMEL_MEDIUM (sigpart)), mem, cancellable, NULL);
	(void) NSS_CMSDecoder_Update (dec, (gchar *) buffer->data, buffer->len);
	cmsg = NSS_CMSDecoder_Finish (dec);
	if (cmsg == NULL) {
		set_nss_error (error, _("Decoder failed"));
		goto fail;
	}

	valid = sm_verify_cmsg (context, cmsg, constream, cancellable, error);

	NSS_CMSMessage_Destroy (cmsg);
fail:
	g_object_unref (mem);
	if (constream)
		g_object_unref (constream);

	return valid;
}
