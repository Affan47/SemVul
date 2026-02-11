test_decrypt (GMimeCryptoContext *ctx, gboolean sign, GMimeStream *cleartext, GMimeStream *ciphertext)
{
	GMimeDecryptResult *result;
	Exception *ex = NULL;
	GMimeStream *stream;
	GError *err = NULL;
	GByteArray *buf[2];

	stream = g_mime_stream_mem_new ();

	if (!(result = g_mime_crypto_context_decrypt (ctx, ciphertext, stream, &err))) {
		g_object_unref (stream);
		ex = exception_new ("%s", err->message);
		g_error_free (err);
		throw (ex);
	}

	if (sign) {
		if (!result->signatures || get_sig_status (result->signatures) != GMIME_SIGNATURE_STATUS_GOOD)
			ex = exception_new ("expected GOOD signature");
	} else {
		if (result->signatures != NULL)
			ex = exception_new ("unexpected signature");
	}

	g_object_unref (result);

	if (ex != NULL) {
		g_object_unref (stream);
		throw (ex);
	}

	buf[0] = GMIME_STREAM_MEM (cleartext)->buffer;
	buf[1] = GMIME_STREAM_MEM (stream)->buffer;

	if (buf[0]->len != buf[1]->len || memcmp (buf[0]->data, buf[1]->data, buf[0]->len) != 0)
		ex = exception_new ("decrypted data does not match original cleartext");

	g_object_unref (stream);

	if (ex != NULL)
		throw (ex);
}
