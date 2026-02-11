are_attachments_mentioned(Compose *compose)
{
	GtkTextView *textview = NULL;
	GtkTextBuffer *textbuffer = NULL;
	GtkTextIter start, end;
	gchar *text = NULL;
	AttachWarnerMention *mention = NULL;
	MatcherList *matchers = NULL;

	matchers = matcherlist_new_from_lines(attwarnerprefs.match_strings, FALSE, attwarnerprefs.case_sensitive);

	if (matchers == NULL) {
		g_warning("couldn't allocate matcher");
		return FALSE;
	}

	textview = GTK_TEXT_VIEW(compose->text);
        textbuffer = gtk_text_view_get_buffer(textview);
	gtk_text_buffer_get_start_iter(textbuffer, &start);
	gtk_text_buffer_get_end_iter(textbuffer, &end);
	text = gtk_text_buffer_get_text(textbuffer, &start, &end, FALSE);

	debug_print("checking text for attachment mentions\n");
	if (text != NULL) {
		mention = aw_matcherlist_string_match(matchers, text, compose->account->sig_sep);
		g_free(text);
	}
	if (matchers != NULL)
		matcherlist_free(matchers);
	debug_print("done\n");
	return mention;
}
