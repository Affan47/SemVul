remove_tag_to_word (GeditAutomaticSpellChecker *spell, const gchar *word)
{
	GtkTextIter iter;
	GtkTextIter match_start, match_end;

	gboolean found;

	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (spell->doc), &iter, 0);

	found = TRUE;

	while (found)
	{
		found = gtk_text_iter_forward_search (&iter,
				word,
				GTK_TEXT_SEARCH_VISIBLE_ONLY | GTK_TEXT_SEARCH_TEXT_ONLY,
				&match_start,
				&match_end,
				NULL);

		if (found)
		{
			if (gtk_text_iter_starts_word (&match_start) &&
			    gtk_text_iter_ends_word (&match_end))
			{
				gtk_text_buffer_remove_tag (GTK_TEXT_BUFFER (spell->doc),
						spell->tag_highlight,
						&match_start,
						&match_end);
			}

			iter = match_end;
		}
	}
}
