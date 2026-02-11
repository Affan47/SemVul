prefs_prepare_cache(void)
{
	gchar *clawsrc = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S, COMMON_RC, NULL);
	gchar *folderitemrc = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S, FOLDERITEM_RC, NULL);
	gchar *accountrc = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S, ACCOUNT_RC, NULL);

	if (whole_cache == NULL) {
		whole_cache = g_hash_table_new_full(g_str_hash, g_str_equal,
				g_free, prefs_destroy_whole_cache);
	} else {
		debug_print("already cached\n");
		g_free(clawsrc);
		g_free(folderitemrc);
		g_free(accountrc);
		return;
	}
	if (prefs_cache(clawsrc) < 0 ||
	    prefs_cache(folderitemrc) < 0 ||
	    prefs_cache(accountrc) < 0)
		prefs_destroy_cache();

	g_free(clawsrc);
	g_free(folderitemrc);
	g_free(accountrc);
}
