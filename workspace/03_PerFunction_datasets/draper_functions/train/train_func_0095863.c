sha1_file_exists (iTunesDB *itdb, gchar *file, gboolean silent)
{
    ExtraiTunesDBData *eitdb;
    Track *track = NULL;

    g_return_val_if_fail (file, NULL);
    g_return_val_if_fail (itdb, NULL);
    eitdb = itdb->userdata;
    g_return_val_if_fail (eitdb, NULL);

    if (prefs_get_int("sha1") && eitdb->sha1hash)
    {
	gchar *val = sha1_hash_on_filename (file, silent);
	if (val)
	{
	    track = g_hash_table_lookup (eitdb->sha1hash, val);
	    g_free (val);
	}
    }
    return track;
}
