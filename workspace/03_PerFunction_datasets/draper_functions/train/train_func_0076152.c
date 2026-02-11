test_nested_fails_with_extra (void)
{
	gboolean ret;
	GBytes *bytes;
	GNode *asn;

	const gchar SEQ_NESTED[] =  "\x30\x0C"
	                                 "\x04\x03""one"
	                                 "\x04\x05""extra";

	asn = egg_asn1x_create (test_asn1_tab, "TestData");
	g_assert ("asn test structure is null" && asn != NULL);

	bytes = g_bytes_new_static (SEQ_NESTED, XL (SEQ_NESTED));
	ret = egg_asn1x_decode (asn, bytes);
	egg_asn1x_assert (ret == FALSE, asn);
	egg_asn1x_assert (strstr (egg_asn1x_message (asn), "encountered extra tag"), asn);
	g_bytes_unref (bytes);

	egg_asn1x_destroy (asn);
}
