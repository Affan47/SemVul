gkm_data_der_read_public_key_dsa (GBytes *data,
                                  gcry_sexp_t *s_key)
{
	GkmDataResult ret = GKM_DATA_UNRECOGNIZED;
	GNode *asn = NULL;
	gcry_mpi_t p, q, g, y;
	int res;

	p = q = g = y = NULL;

	asn = egg_asn1x_create_and_decode (pk_asn1_tab, "DSAPublicKey", data);
	if (!asn)
		goto done;

	ret = GKM_DATA_FAILURE;

	if (!gkm_data_asn1_read_mpi (egg_asn1x_node (asn, "p", NULL), &p) ||
	    !gkm_data_asn1_read_mpi (egg_asn1x_node (asn, "q", NULL), &q) ||
	    !gkm_data_asn1_read_mpi (egg_asn1x_node (asn, "g", NULL), &g) ||
	    !gkm_data_asn1_read_mpi (egg_asn1x_node (asn, "Y", NULL), &y))
		goto done;

	res = gcry_sexp_build (s_key, NULL, SEXP_PUBLIC_DSA, p, q, g, y);
	if (res)
		goto done;

	g_assert (*s_key);
	ret = GKM_DATA_SUCCESS;

done:
	egg_asn1x_destroy (asn);
	gcry_mpi_release (p);
	gcry_mpi_release (q);
	gcry_mpi_release (g);
	gcry_mpi_release (y);

	if (ret == GKM_DATA_FAILURE)
		g_message ("invalid public DSA key");

	return ret;
}
