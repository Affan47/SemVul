entry_strsplit_utf8 (GtkEntry *entry,
                     gchar ***set,
                     gint **starts,
                     gint **ends)
{
	PangoLayout *layout;
	PangoLogAttr *log_attrs;
	const gchar *text;
	gint n_attrs, n_strings, i, j;

	layout = gtk_entry_get_layout (GTK_ENTRY (entry));
	text = gtk_entry_get_text (GTK_ENTRY (entry));
	pango_layout_get_log_attrs (layout, &log_attrs, &n_attrs);


	n_strings = 0;
	for (i = 0; i < n_attrs; i++)
		if (log_attrs[i].is_word_start)
			n_strings++;

	*set = g_new0 (gchar *, n_strings + 1);
	*starts = g_new0 (gint, n_strings);
	*ends = g_new0 (gint, n_strings);


	for (i = 0, j = 0; i < n_attrs; i++) {
		if (log_attrs[i].is_word_start) {
			gint cend, bytes;
			gchar *start;


			cend = i;
			while (!(log_attrs[cend].is_word_end))
				cend++;


			start = g_utf8_offset_to_pointer (text, i);
			bytes = (gint) (g_utf8_offset_to_pointer (text, cend) - start);
			(*set)[j] = g_new0 (gchar, bytes + 1);
			(*starts)[j] = (gint) (start - text);
			(*ends)[j] = (gint) (start - text + bytes);
			g_utf8_strncpy ((*set)[j], start, cend - i);


			j++;
		}
	}

	g_free (log_attrs);
}
