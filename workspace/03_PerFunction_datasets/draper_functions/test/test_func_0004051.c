get_next_misspelled_word (GeditView *view)
{
	GeditDocument *doc;
	CheckRange *range;
	gint start, end;
	gchar *word;
	GeditSpellChecker *spell;

	g_return_val_if_fail (view != NULL, NULL);

	doc = GEDIT_DOCUMENT (gtk_text_view_get_buffer (GTK_TEXT_VIEW (view)));
	g_return_val_if_fail (doc != NULL, NULL);

	range = get_check_range (doc);
	g_return_val_if_fail (range != NULL, NULL);

	spell = get_spell_checker_from_document (doc);
	g_return_val_if_fail (spell != NULL, NULL);

	word = get_current_word (doc, &start, &end);
	if (word == NULL)
		return NULL;

	gedit_debug_message (DEBUG_PLUGINS, "Word to check: %s", word);

	while (gedit_spell_checker_check_word (spell, word, -1))
	{
		g_free (word);

		if (!goto_next_word (doc))
			return NULL;


		word = get_current_word (doc, &start, &end);
		if (word == NULL)
			return NULL;

		gedit_debug_message (DEBUG_PLUGINS, "Word to check: %s", word);
	}

	if (!goto_next_word (doc))
		update_current (doc, gtk_text_buffer_get_char_count (GTK_TEXT_BUFFER (doc)));

	if (word != NULL)
	{
		GtkTextIter s, e;

		range->mw_start = start;
		range->mw_end = end;

		gedit_debug_message (DEBUG_PLUGINS, "Select [%d, %d]", start, end);

		gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (doc), &s, start);
		gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (doc), &e, end);

		gtk_text_buffer_select_range (GTK_TEXT_BUFFER (doc), &s, &e);

		gedit_view_scroll_to_cursor (view);
	}
	else
	{
		range->mw_start = -1;
		range->mw_end = -1;
	}

	return word;
}
