test_entry_removed_signal (Test *test, gconstpointer unused)
{
	GkmDataResult res;
	gboolean removed;

	g_signal_connect (test->data_file, "entry-removed", G_CALLBACK (entry_removed_one), &removed);


	removed = FALSE;
	res = gkm_gnome2_file_read_fd (test->data_file, test->public_fd, NULL);
	g_assert (res == GKM_DATA_SUCCESS);
	g_assert (removed == FALSE);


	removed = FALSE;
	res = gkm_gnome2_file_destroy_entry (test->data_file, "non-existant");
	g_assert (res == GKM_DATA_UNRECOGNIZED);
	g_assert (removed == FALSE);


	removed = FALSE;
	res = gkm_gnome2_file_destroy_entry (test->data_file, "identifier-public");
	g_assert (res == GKM_DATA_SUCCESS);
	g_assert (removed == TRUE);


	res = gkm_gnome2_file_create_entry (test->data_file, "extra-dummy", GKM_GNOME2_FILE_SECTION_PUBLIC);
	g_assert (res == GKM_DATA_SUCCESS);


	removed = FALSE;
	g_assert (lseek (test->public_fd, 0, SEEK_SET) != -1);
	res = gkm_gnome2_file_read_fd (test->data_file, test->public_fd, NULL);
	g_assert (res == GKM_DATA_SUCCESS);
	g_assert (removed == TRUE);
}
