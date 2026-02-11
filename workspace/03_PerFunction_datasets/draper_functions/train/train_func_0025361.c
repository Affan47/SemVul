vcalviewer_get_uid_from_mimeinfo(MimeInfo *mimeinfo)
{
	gchar *tmpfile = procmime_get_tmp_file_name(mimeinfo);
	const gchar *charset = procmime_mimeinfo_get_parameter(mimeinfo, "charset");
	gchar *compstr = NULL;
	gchar *res = NULL;
	VCalEvent *event = NULL;

	if (!charset)
		charset = CS_WINDOWS_1252;

	if (!strcasecmp(charset, CS_ISO_8859_1))
		charset = CS_WINDOWS_1252;

	if (procmime_get_part(tmpfile, mimeinfo) < 0) {
		g_warning("Can't get mimepart file");
		g_free(tmpfile);
		return NULL;
	}

	compstr = file_read_to_str(tmpfile);

	event = vcal_get_event_from_ical(compstr, charset);
	if (event)
		res = g_strdup(event->uid);

	vcal_manager_free_event(event);

	debug_print("got uid: %s\n", res);
	return res;

}
