gkm_data_der_read_public_key_rsa (GBytes *data,
                                  gcry_sexp_t *s_key)
{
	GkmDataResult ret = GKM_DATA_UNRECOGNIZED;
	GNode *asn = NULL;
	gcry_mpi_t n, e;
	int res;

	n = e = NULL;

	asn = egg_asn1x_create_and_decode (pk_asn1_tab, "RSAPublicKey", data);
	if (!asn)
		goto done;

	ret = GKM_DATA_FAILURE;

	if (!gkm_data_asn1_read_mpi (egg_asn1x_node (asn, "modulus", NULL), &n) ||
	    !gkm_data_asn1_read_mpi (egg_asn1x_node (asn, "publicExponent", NULL), &e))
		goto done;

	res = gcry_sexp_build (s_key, NULL, SEXP_PUBLIC_RSA, n, e);
	if (res)
		goto done;

	g_assert (*s_key);
	ret = GKM_DATA_SUCCESS;

done:
	egg_asn1x_destroy (asn);
	gcry_mpi_release (n);
	gcry_mpi_release (e);

	if (ret == GKM_DATA_FAILURE)
		g_message ("invalid RSA public key");

	return ret;
}
