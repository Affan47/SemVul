test_enumerated (void)
{
	GBytes *bytes;
	GNode *asn;
	GBytes *data;
	GQuark value;

	bytes = g_bytes_new_static (ENUM_TWO, XL (ENUM_TWO));
	asn = egg_asn1x_create_and_decode (test_asn1_tab, "TestEnumerated", bytes);
	g_assert (asn != NULL);
	g_bytes_unref (bytes);

	g_assert_cmpint (EGG_ASN1X_ENUMERATED, ==, egg_asn1x_type (asn));

	value = egg_asn1x_get_enumerated (asn);
	g_assert (value);
	g_assert_cmpstr (g_quark_to_string (value), ==, "valueTwo");

	egg_asn1x_set_enumerated (asn, g_quark_from_static_string ("valueThree"));

	data = egg_asn1x_encode (asn, NULL);
	g_assert (data != NULL);

	egg_assert_cmpbytes (data, ==, ENUM_THREE, XL (ENUM_THREE));

	g_bytes_unref (data);
	egg_asn1x_destroy (asn);
}
