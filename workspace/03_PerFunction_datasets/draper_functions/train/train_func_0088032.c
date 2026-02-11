test_oid_decode_bad (void)
{
	GBytes *bytes;
	GNode *asn;
	gboolean ret;


	const gchar INVALID_OID[] = "\x30\x07\x06\x05\x2b\x80\x83\x82\x1a";

	asn = egg_asn1x_create (test_asn1_tab, "TestOid");
	g_assert ("asn test structure is null" && asn != NULL);

	bytes = g_bytes_new_static (INVALID_OID, XL (INVALID_OID));
	ret = egg_asn1x_decode (asn, bytes);
	g_assert (ret == FALSE);
	g_assert (strstr (egg_asn1x_message (asn), "object id encoding is invalid") != NULL);

	g_bytes_unref (bytes);
	egg_asn1x_destroy (asn);
}
