gkm_data_der_read_public_key_dsa_parts (GBytes *keydata,
                                        GBytes *params,
                                        gcry_sexp_t *s_key)
{
	gcry_mpi_t p, q, g, y;
	GkmDataResult ret = GKM_DATA_UNRECOGNIZED;
	GNode *asn_params = NULL;
	GNode *asn_key = NULL;
	int res;

	p = q = g = y = NULL;

	asn_params = egg_asn1x_create_and_decode (pk_asn1_tab, "DSAParameters", params);
	asn_key = egg_asn1x_create_and_decode (pk_asn1_tab, "DSAPublicPart", keydata);
	if (!asn_params || !asn_key)
		goto done;

	ret = GKM_DATA_FAILURE;

	if (!gkm_data_asn1_read_mpi (egg_asn1x_node (asn_params, "p", NULL), &p) ||
	    !gkm_data_asn1_read_mpi (egg_asn1x_node (asn_params, "q", NULL), &q) ||
	    !gkm_data_asn1_read_mpi (egg_asn1x_node (asn_params, "g", NULL), &g))
		goto done;

	if (!gkm_data_asn1_read_mpi (asn_key, &y))
		goto done;

	res = gcry_sexp_build (s_key, NULL, SEXP_PUBLIC_DSA, p, q, g, y);
	if (res)
		goto done;

	g_assert (*s_key);
	ret = GKM_DATA_SUCCESS;

done:
	egg_asn1x_destroy (asn_key);
	egg_asn1x_destroy (asn_params);
	gcry_mpi_release (p);
	gcry_mpi_release (q);
	gcry_mpi_release (g);
	gcry_mpi_release (y);

	if (ret == GKM_DATA_FAILURE)
		g_message ("invalid DSA key");

	return ret;
}
