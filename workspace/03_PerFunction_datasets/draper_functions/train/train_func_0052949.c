test_pkcs12_decode (Test *test,
                    gconstpointer unused)
{
	GNode *asn;
	gboolean ret;

	asn = egg_asn1x_create (pkix_asn1_tab, "pkcs-12-PFX");

	if (g_test_verbose ())
		egg_asn1x_dump (asn);

	ret = egg_asn1x_decode (asn, test->data);
	egg_asn1x_assert (ret == TRUE, asn);

	egg_asn1x_destroy (asn);
}
