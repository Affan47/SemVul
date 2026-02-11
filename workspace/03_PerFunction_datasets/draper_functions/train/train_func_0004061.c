test_recreate_keyring (void)
{
	GnomeKeyringResult res;


	res = gnome_keyring_create_sync (KEYRING_NAME, PASSWORD);
	g_assert_cmpint (GNOME_KEYRING_RESULT_OK, ==, res);
	res = gnome_keyring_set_default_keyring_sync (KEYRING_NAME);
	g_assert_cmpint (GNOME_KEYRING_RESULT_OK, ==, res);
}
