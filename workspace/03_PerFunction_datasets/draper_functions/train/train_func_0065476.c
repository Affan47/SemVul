test_create_quark (void)
{
	GNode *asn;

	asn = egg_asn1x_create_quark (test_asn1_tab, g_quark_from_static_string ("1.5.13"));
	g_assert (asn != NULL);
	g_assert_cmpstr (egg_asn1x_name (asn), ==, "TestIntegers");
}
