prefs_display_header_write_config(void)
{
	gchar *rcpath;
	PrefFile *pfile;
	GSList *cur;

	debug_print("Writing configuration for displaying headers...\n");

	rcpath = g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S,
			     DISPLAY_HEADER_RC, NULL);

	if ((pfile = prefs_write_open(rcpath)) == NULL) {
		g_warning("failed to write configuration to file\n");
		g_free(rcpath);
		return;
	}

	for (cur = prefs_common.disphdr_list; cur != NULL;
	     cur = cur->next) {
		DisplayHeaderProp *dp = (DisplayHeaderProp *)cur->data;
		gchar *dpstr;

		dpstr = display_header_prop_get_str(dp);
		if (fputs(dpstr, pfile->fp) == EOF ||
		    fputc('\n', pfile->fp) == EOF) {
			FILE_OP_ERROR(rcpath, "fputs || fputc");
			prefs_file_close_revert(pfile);
			g_free(rcpath);
			g_free(dpstr);
			return;
		}
		g_free(dpstr);
	}

	g_free(rcpath);

	if (prefs_file_close(pfile) < 0) {
		g_warning("failed to write configuration to file\n");
		return;
	}
}
