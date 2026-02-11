test_asn1_integers (Test *test, gconstpointer unused)
{
	GNode *asn;
	gcry_mpi_t mpi, mpt;
	GBytes *data;
	gboolean ret;

	asn = egg_asn1x_create (test_asn1_tab, "TestIntegers");
	g_assert ("asn test structure is null" && asn != NULL);


	mpi = gcry_mpi_new (512);
	g_return_if_fail (mpi);
	gcry_mpi_randomize (mpi, 512, GCRY_WEAK_RANDOM);


	ret = gkm_data_asn1_write_mpi (egg_asn1x_node (asn, "mpi", NULL), mpi);


	data = egg_asn1x_encode (asn, NULL);
	g_assert ("encoding asn1 didn't work" && data != NULL);

	egg_asn1x_destroy (asn);


	asn = egg_asn1x_create_and_decode (test_asn1_tab, "TestIntegers", data);
	g_assert (asn != NULL);

	ret = gkm_data_asn1_read_mpi (egg_asn1x_node (asn, "mpi", NULL), &mpt);
	g_assert ("couldn't read mpi from asn1" && ret);
	g_assert ("mpi returned is null" && mpt != NULL);
	g_assert ("mpi is wrong number" && gcry_mpi_cmp (mpi, mpt) == 0);

	g_bytes_unref (data);
}
