invalidate_count_and_unref (gpointer key, gpointer value, gpointer user_data)
{
	g_assert (NAUTILUS_IS_DIRECTORY (key));
	g_assert (value == key);
	g_assert (user_data == NULL);

	nautilus_directory_invalidate_count_and_mime_list (key);
	nautilus_directory_unref (key);
}
