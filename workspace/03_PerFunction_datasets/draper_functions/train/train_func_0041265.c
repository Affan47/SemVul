nemo_file_matches_uri (NemoFile *file, const char *match_uri)
{
	GFile *match_file, *location;
	gboolean result;

	g_return_val_if_fail (NEMO_IS_FILE (file), FALSE);
	g_return_val_if_fail (match_uri != NULL, FALSE);

	location = nemo_file_get_location (file);
	match_file = g_file_new_for_uri (match_uri);
	result = g_file_equal (location, match_file);
	g_object_unref (location);
	g_object_unref (match_file);

	return result;
}
