test_equal (void)
{
	GkmSecret *one;
	GkmSecret *two;

	one = two = gkm_secret_new ((CK_UTF8CHAR_PTR)"funny", 5);
	g_assert (gkm_secret_equal (one, two));

	two = gkm_secret_new_from_password ("funny");
	g_assert (gkm_secret_equal (one, two));

	g_object_unref (one);
	one = gkm_secret_new_from_password ("other");
	g_assert (!gkm_secret_equal (one, two));
}
