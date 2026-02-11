test_encode (void)
{
	gchar *hex;

	hex = egg_hex_encode (TEST_DATA, sizeof (TEST_DATA));
	g_assert (hex);
	g_assert_cmpstr (hex, ==, TEST_HEX);

	g_free (hex);
}
