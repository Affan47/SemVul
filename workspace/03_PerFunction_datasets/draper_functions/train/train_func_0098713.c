test_octet_string_set_as_bytes (void)
{
	GBytes *bytes;
	GNode *asn;

	asn = egg_asn1x_create (test_asn1_tab, "TestOctetString");
	g_assert (asn != NULL);

	bytes = g_bytes_new_static ("farnsworth", 10);
	egg_asn1x_set_string_as_bytes (asn, bytes);
	g_bytes_unref (bytes);

	bytes = egg_asn1x_encode (asn, NULL);
	g_assert (bytes != NULL);
	egg_assert_cmpbytes (bytes, ==, SFARNSWORTH, XL (SFARNSWORTH));
	g_bytes_unref (bytes);

	egg_asn1x_destroy (asn);
}
