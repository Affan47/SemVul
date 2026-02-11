invalidate_one_count (gpointer key, gpointer value, gpointer user_data)
{
	NemoDirectory *directory;

	g_assert (key != NULL);
	g_assert (NEMO_IS_DIRECTORY (value));
	g_assert (user_data == NULL);

	directory = NEMO_DIRECTORY (value);

	nemo_directory_invalidate_count_and_mime_list (directory);
}
