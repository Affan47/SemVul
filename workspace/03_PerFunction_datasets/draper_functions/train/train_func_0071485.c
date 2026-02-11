prefs_display_header_read_config(void)
{
	gchar *rcpath;
	FILE *fp;
	gchar buf[PREFSBUFSIZE];
	DisplayHeaderProp *dp;

	debug_print("Reading configuration for displaying headers...\n");

	rcpath = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S,
			     DISPLAY_HEADER_RC, NULL);
	if ((fp = g_fopen(rcpath, "rb")) == NULL) {
		if (ENOENT != errno) FILE_OP_ERROR(rcpath, "fopen");
		g_free(rcpath);
		prefs_common.disphdr_list = NULL;
		prefs_display_header_set_default();
		return;
	}
	g_free(rcpath);


	while (prefs_common.disphdr_list != NULL) {
		dp = (DisplayHeaderProp *)prefs_common.disphdr_list->data;
		display_header_prop_free(dp);
		prefs_common.disphdr_list =
			g_slist_remove(prefs_common.disphdr_list, dp);
	}

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		g_strdelimit(buf, "\r\n", '\0');
		dp = display_header_prop_read_str(buf);
		if (dp)
			prefs_common.disphdr_list =
				g_slist_append(prefs_common.disphdr_list, dp);
	}

	fclose(fp);
}
