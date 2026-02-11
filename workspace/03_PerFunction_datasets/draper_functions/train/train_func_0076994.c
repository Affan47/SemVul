get_hover_msg (const gchar *url)
{
	char * str;
	gpointer addr = NULL;


	str = strstr (url, "0x");
	if (str)
	{
		addr = (gpointer) strtoul (str, NULL, 16);
	}


	if (addr && (0 == strncmp ("gtt:task:", url, 9)))
	{
		GttTask *task = addr;
		const char * memo = gtt_task_get_memo(task);
		const char * notes = gtt_task_get_notes(task);
		char * msg = g_strdup_printf ("<b><big>%s</big></b>\n%s\n", memo, notes);
		return msg;
	}

	if (0 == strncmp (url, "gtt:proj:", 9))
	{
		GttProject *prj = addr;
		const char * title = gtt_project_get_title (prj);
		const char * desc = gtt_project_get_desc (prj);
		const char * notes = gtt_project_get_notes (prj);
		char * msg = g_strdup_printf ("<b><big>%s</big></b>\n"
		                              "<b>%s</b>\n"
		                              "%s", title, desc, notes);
		return msg;
	}

	char * msg = _("Left-click to bring up menu");
	return g_strdup (msg);
}
