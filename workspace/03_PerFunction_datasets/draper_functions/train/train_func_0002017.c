handle_pkcs12_encrypted_bag (GcrParser *self,
                             GNode *bag)
{
	PasswordState pstate = PASSWORD_STATE_INIT;
	GNode *asn = NULL;
	gcry_cipher_hd_t cih = NULL;
	gcry_error_t gcry;
	guchar *crypted = NULL;
	GNode *params = NULL;
	gsize n_crypted;
	const gchar *password;
	GBytes *cbytes;
	GQuark scheme;
	gint ret, r;
	gint l;

	ret = GCR_ERROR_UNRECOGNIZED;

	asn = egg_asn1x_get_any_as_full (bag, pkix_asn1_tab, "pkcs-7-EncryptedData",
	                                 EGG_ASN1X_NO_STRICT);
	if (!asn)
		goto done;

	ret = GCR_ERROR_FAILURE;


	scheme = egg_asn1x_get_oid_as_quark (egg_asn1x_node (asn, "encryptedContentInfo", "contentEncryptionAlgorithm", "algorithm", NULL));
	if (!scheme)
		goto done;

	params = egg_asn1x_node (asn, "encryptedContentInfo", "contentEncryptionAlgorithm", "parameters", NULL);
	if (!params)
		goto done;


	for (;;) {

		g_assert (cih == NULL);

		r = enum_next_password (self, &pstate, &password);
		if (r != SUCCESS) {
			ret = r;
			goto done;
		}


		if (!egg_symkey_read_cipher (scheme, password, -1, params, &cih)) {
			ret = GCR_ERROR_FAILURE;
			goto done;
		}

		crypted = egg_asn1x_get_string_as_raw (egg_asn1x_node (asn, "encryptedContentInfo", "encryptedContent", NULL),
		                                       egg_secure_realloc, &n_crypted);
		if (!crypted)
			goto done;

		gcry = gcry_cipher_decrypt (cih, crypted, n_crypted, NULL, 0);
		gcry_cipher_close (cih);
		cih = NULL;

		if (gcry != 0) {
			g_warning ("couldn't decrypt pkcs12 data: %s", gcry_strerror (gcry));
			goto done;
		}


		l = egg_asn1x_element_length (crypted, n_crypted);
		if (l > 0)
			n_crypted = l;

		cbytes = g_bytes_new_with_free_func (crypted, n_crypted, egg_secure_free, crypted);
		crypted = NULL;


		r = handle_pkcs12_bag (self, cbytes);
		g_bytes_unref (cbytes);

		if (r != GCR_ERROR_UNRECOGNIZED) {
			ret = r;
			break;
		}


	}

done:
	if (cih)
		gcry_cipher_close (cih);
	egg_asn1x_destroy (asn);
	egg_secure_free (crypted);
	return ret;
}
