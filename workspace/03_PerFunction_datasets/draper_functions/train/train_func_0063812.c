about_update_stats(void)
{
	if (stats_text_buffer != NULL)
	{
		GtkTextIter start, end, iter;
		gchar buf[1024];

		gtk_text_buffer_get_start_iter(stats_text_buffer, &start);
		gtk_text_buffer_get_end_iter(stats_text_buffer, &end);
		gtk_text_buffer_delete(stats_text_buffer, &start, &end);

		gtk_text_buffer_get_iter_at_offset(stats_text_buffer, &iter, 0);

		gtk_text_buffer_insert_with_tags_by_name(stats_text_buffer, &iter,
				(_("Session statistics\n")), -1,
				"underlined-list-title", NULL);

		if (prefs_common.date_format) {
			struct tm *lt;
			gint len = 100;
			gchar date[len];

			lt = localtime(&session_stats.time_started);
			fast_strftime(date, len, prefs_common.date_format, lt);
			g_snprintf(buf, sizeof(buf), _("Started: %s\n"),
						lt ? date : ctime(&session_stats.time_started));
		} else
			g_snprintf(buf, sizeof(buf), _("Started: %s\n"),
						ctime(&session_stats.time_started));
		gtk_text_buffer_insert_with_tags_by_name(stats_text_buffer, &iter, buf, -1,
				"indented-list-item", NULL);

		gtk_text_buffer_insert(stats_text_buffer, &iter, "\n", 1);
		gtk_text_buffer_insert_with_tags_by_name(stats_text_buffer, &iter,
				(_("Incoming traffic\n")), -1,
				"underlined-list-title", NULL);

		g_snprintf(buf, sizeof(buf), _("Received messages: %d\n"),
					session_stats.received);
		gtk_text_buffer_insert_with_tags_by_name(stats_text_buffer, &iter, buf, -1,
				"indented-list-item", "bold", NULL);

		gtk_text_buffer_insert(stats_text_buffer, &iter, "\n", 1);
		gtk_text_buffer_insert_with_tags_by_name(stats_text_buffer, &iter,
				(_("Outgoing traffic\n")), -1,
				"underlined-list-title", NULL);

		g_snprintf(buf, sizeof(buf), _("New/redirected messages: %d\n"),
					session_stats.sent);
		gtk_text_buffer_insert_with_tags_by_name(stats_text_buffer, &iter, buf, -1,
				"indented-list-item", NULL);

		g_snprintf(buf, sizeof(buf), _("Replied messages: %d\n"),
					session_stats.replied);
		gtk_text_buffer_insert_with_tags_by_name(stats_text_buffer, &iter, buf, -1,
				"indented-list-item", NULL);

		g_snprintf(buf, sizeof(buf), _("Forwarded messages: %d\n"),
					session_stats.forwarded);
		gtk_text_buffer_insert_with_tags_by_name(stats_text_buffer, &iter, buf, -1,
				"indented-list-item", NULL);

		g_snprintf(buf, sizeof(buf), _("Total outgoing messages: %d\n"),
					(session_stats.sent + session_stats.replied +
					 session_stats.forwarded));
		gtk_text_buffer_insert_with_tags_by_name(stats_text_buffer, &iter, buf, -1,
				"indented-list-item", "bold", NULL);
	}
}
