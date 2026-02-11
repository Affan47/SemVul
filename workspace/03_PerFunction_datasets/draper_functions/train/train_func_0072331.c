scan_func(GNode *node, gpointer data)
{
	struct clamd_result *result = (struct clamd_result *) data;
	MimeInfo *mimeinfo = (MimeInfo *) node->data;
	gchar *outfile;
	response buf;
	int max;
	struct stat info;
	gchar* msg;

	outfile = procmime_get_tmp_file_name(mimeinfo);
	if (procmime_get_part(outfile, mimeinfo) < 0)
		g_warning("Can't get the part of multipart message.");
	else {
    	max = config.clamav_max_size * 1048576;
		if (stat(outfile, &info) == -1)
			g_warning("Can't determine file size");
		else {
			if (info.st_size <= max) {
				debug_print("Scanning %s\n", outfile);
				result->status = clamd_verify_email(outfile, &buf);
				debug_print("status: %d\n", result->status);
				switch (result->status) {
					case NO_SOCKET:
						g_warning("[scanning] No socket information");
						alertpanel_error(_("Scanning\nNo socket information.\nAntivirus disabled."));
						break;
					case NO_CONNECTION:
						g_warning("[scanning] Clamd does not respond to ping");
						alertpanel_warning(_("Scanning\nClamd does not respond to ping.\nIs clamd running?"));
						break;
					case VIRUS:
						msg = g_strconcat(_("Detected %s virus."),
							clamd_get_virus_name(buf.msg), NULL);
						g_warning("%s\n", msg);
						debug_print("no_recv: %d\n", prefs_common.no_recv_err_panel);
						if (prefs_common.no_recv_err_panel) {
						    statusbar_print_all("%s", msg);
						}
						else {
						    alertpanel_warning("%s\n", msg);
						}
						g_free(msg);
						break;
					case SCAN_ERROR:
						debug_print("Error: %s\n", buf.msg);
						alertpanel_error(_("Scanning error:\n%s"), buf.msg);
						break;
					case OK:
						debug_print("No virus detected.\n");
						break;
				}
			}
			else {
				debug_print("File: %s. Size (%d) greater than limit (%d)\n",
							outfile, (int) info.st_size, max);
			}
		}
		g_unlink(outfile);
	}

	return (result->status == OK) ? FALSE : TRUE;
}
