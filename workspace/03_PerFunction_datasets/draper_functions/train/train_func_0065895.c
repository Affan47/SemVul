test_write_private_with_login (Test *test, gconstpointer unused)
{
	GkmDataResult res;
	gulong value;

	res = gkm_gnome2_file_create_entry (test->data_file, "identifier-public", GKM_GNOME2_FILE_SECTION_PUBLIC);
	g_assert (res == GKM_DATA_SUCCESS);
	res = gkm_gnome2_file_write_value (test->data_file, "identifier-public", CKA_LABEL, "public-label", 12);
	g_assert (res == GKM_DATA_SUCCESS);

	res = gkm_gnome2_file_create_entry (test->data_file, "identifier-two", GKM_GNOME2_FILE_SECTION_PUBLIC);
	g_assert (res == GKM_DATA_SUCCESS);
	res = gkm_gnome2_file_write_value (test->data_file, "identifier-two", CKA_LABEL, "TWO-label", 9);
	g_assert (res == GKM_DATA_SUCCESS);
	value = 555;
	res = gkm_gnome2_file_write_value (test->data_file, "identifier-two", CKA_VALUE, &value, sizeof (value));
	g_assert (res == GKM_DATA_SUCCESS);

	res = gkm_gnome2_file_create_entry (test->data_file, "identifier-private", GKM_GNOME2_FILE_SECTION_PRIVATE);
	g_assert (res == GKM_DATA_SUCCESS);
	res = gkm_gnome2_file_write_value (test->data_file, "identifier-private", CKA_LABEL, "private-label", 13);
	g_assert (res == GKM_DATA_SUCCESS);

	res = gkm_gnome2_file_write_fd (test->data_file, test->write_fd, test->login);
	g_assert (res == GKM_DATA_SUCCESS);
}
