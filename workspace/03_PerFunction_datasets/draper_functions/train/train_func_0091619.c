create_dsa_public (CK_ATTRIBUTE_PTR attrs, CK_ULONG n_attrs, gcry_sexp_t *skey)
{
	gcry_error_t gcry;
	gcry_mpi_t p = NULL;
	gcry_mpi_t q = NULL;
	gcry_mpi_t g = NULL;
	gcry_mpi_t y = NULL;
	CK_RV ret;

	if (!gkm_attributes_find_mpi (attrs, n_attrs, CKA_PRIME, &p) ||
	    !gkm_attributes_find_mpi (attrs, n_attrs, CKA_SUBPRIME, &q) ||
	    !gkm_attributes_find_mpi (attrs, n_attrs, CKA_BASE, &g) ||
	    !gkm_attributes_find_mpi (attrs, n_attrs, CKA_VALUE, &y)) {
		ret = CKR_TEMPLATE_INCOMPLETE;
		goto done;
	}

	gcry = gcry_sexp_build (skey, NULL,
	                        "(public-key (dsa (p %m) (q %m) (g %m) (y %m)))",
	                        p, q, g, y);

	if (gcry != 0) {
		g_message ("couldn't create DSA key from passed attributes: %s", gcry_strerror (gcry));
		ret = CKR_FUNCTION_FAILED;
		goto done;
	}

	gkm_attributes_consume (attrs, n_attrs, CKA_PRIME, CKA_SUBPRIME,
	                        CKA_BASE, CKA_VALUE, G_MAXULONG);
	ret = CKR_OK;

done:
	gcry_mpi_release (p);
	gcry_mpi_release (q);
	gcry_mpi_release (g);
	gcry_mpi_release (y);
	return ret;
}
