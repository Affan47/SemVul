markup_text (GtkTextBuffer *buffer)
{
	GtkTextIter start, end;
	gchar *text;
	gint i;
	regmatch_t pmatch[2];
	gboolean any;
	const gchar *str;
	gint offset = 0;

	g_return_if_fail (buffer != NULL);

	gtk_text_buffer_get_start_iter (buffer, &start);
	gtk_text_buffer_get_end_iter (buffer, &end);
	gtk_text_buffer_remove_tag_by_name (buffer, E_BUFFER_TAGGER_LINK_TAG, &start, &end);
	text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);

	str = text;
	any = TRUE;
	while (any) {
		any = FALSE;
		for (i = 0; i < G_N_ELEMENTS (mim); i++) {
			if (mim[i].preg && !regexec (mim[i].preg, str, 2, pmatch, 0)) {
				gtk_text_buffer_get_iter_at_offset (buffer, &start, offset + pmatch[0].rm_so);
				gtk_text_buffer_get_iter_at_offset (buffer, &end, offset + pmatch[0].rm_eo);
				gtk_text_buffer_apply_tag_by_name (buffer, E_BUFFER_TAGGER_LINK_TAG, &start, &end);

				any = TRUE;
				str += pmatch[0].rm_eo;
				offset += pmatch[0].rm_eo;
				break;
			}
		}
	}

	g_free (text);
}
