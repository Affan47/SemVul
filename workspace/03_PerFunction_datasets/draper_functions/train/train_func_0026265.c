mpi_from_data (const guchar *data,
               gsize n_data)
{
	gcry_mpi_t mpi;
	gcry_error_t gcry;

	gcry = gcry_mpi_scan (&mpi, GCRYMPI_FMT_USG, data, n_data, NULL);
	return (gcry == 0) ? mpi : NULL;
}
