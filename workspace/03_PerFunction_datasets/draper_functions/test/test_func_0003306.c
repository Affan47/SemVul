crypto_is_pkcs12_data (const GByteArray *data)
{
	GError *error = NULL;
	gboolean success;

	g_return_val_if_fail (data != NULL, FALSE);

	success = crypto_verify_pkcs12 (data, NULL, &error);
	if (success == FALSE) {

		if (error) {
			if (g_error_matches (error, NM_CRYPTO_ERROR, NM_CRYPTO_ERR_CIPHER_DECRYPT_FAILED))
				success = TRUE;
			g_error_free (error);
		}
	}
	return success;
}
