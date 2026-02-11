test_attribute_find_mpi (void)
{
	gcry_mpi_t mpi = NULL;
	gboolean ret;

	ret = gkm_attributes_find_mpi (attr_template, G_N_ELEMENTS (attr_template), CKA_VALUE, &mpi);
	g_assert (ret == TRUE);
	g_assert (mpi != NULL);

	g_assert (gcry_mpi_cmp_ui (mpi, 123456789) == 0);
	gcry_mpi_release (mpi);
}
