gkm_crypto_sexp_to_data (gcry_sexp_t sexp, guint bits, CK_BYTE_PTR data,
                         CK_ULONG *n_data, EggPadding padding, ...)
{
	gcry_sexp_t at = NULL;
	gsize n_block, offset, len;
	gcry_mpi_t mpi = NULL;
	gpointer padded;
	guchar *block;
	va_list va;
	gboolean ret;
	gcry_error_t gcry;

	g_assert (sexp);
	g_assert (data);
	g_assert (n_data);
	g_assert (bits);


	va_start (va, padding);
	at = gkm_sexp_get_childv (sexp, va);
	va_end (va);


	g_return_val_if_fail (at != NULL, CKR_GENERAL_ERROR);


	mpi = gcry_sexp_nth_mpi (at, 1, GCRYMPI_FMT_USG);
	g_return_val_if_fail (at != NULL, CKR_GENERAL_ERROR);
	gcry_sexp_release (at);


	n_block = (bits + 7) / 8;
	gcry = gcry_mpi_print (GCRYMPI_FMT_USG, NULL, 0, &len, mpi);
	g_return_val_if_fail (gcry == 0, CKR_GENERAL_ERROR);
	g_return_val_if_fail (len <= n_block, CKR_GENERAL_ERROR);
	offset = n_block - len;
	block = g_malloc0 (n_block);
	memset (block, 0, offset);
	gcry = gcry_mpi_print (GCRYMPI_FMT_USG, block + offset, len, &len, mpi);
	g_return_val_if_fail (gcry == 0, CKR_GENERAL_ERROR);
	g_return_val_if_fail (len == n_block - offset, CKR_GENERAL_ERROR);
	gcry_mpi_release (mpi);


	if (padding != NULL) {
		ret = (padding) (g_realloc, n_block, block, n_block, &padded, &n_block);
		g_free (block);
		if (ret == FALSE)
			return CKR_DATA_LEN_RANGE;
		block = padded;
	}


	if (n_block > *n_data)
		return CKR_BUFFER_TOO_SMALL;

	memcpy (data, block, n_block);
	*n_data = n_block;
	g_free (block);

	return CKR_OK;
}
