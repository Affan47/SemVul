backward_lines_match (const GtkTextIter *start,
		      const gchar      **lines,
		      gboolean           visible_only,
		      gboolean           slice,
		      GtkTextIter       *match_start,
		      GtkTextIter       *match_end)
{
	GtkTextIter line, next;
	gchar *line_text;
	const gchar *found;
	gint offset;

	if (*lines == NULL || **lines == '\0')
	{
		if (match_start)
			*match_start = *start;
		if (match_end)
			*match_end = *start;
		return TRUE;
	}

	line = next = *start;
	if (gtk_text_iter_get_line_offset (&next) == 0)
	{
		if (!gtk_text_iter_backward_line (&next))
			return FALSE;
	}
	else
		gtk_text_iter_set_line_offset (&next, 0);

	if (slice)
	{
		if (visible_only)
			line_text = gtk_text_iter_get_visible_slice (&next, &line);
		else
			line_text = gtk_text_iter_get_slice (&next, &line);
	}
	else
	{
		if (visible_only)
			line_text = gtk_text_iter_get_visible_text (&next, &line);
		else
			line_text = gtk_text_iter_get_text (&next, &line);
	}

	if (match_start)
	{
		found = g_utf8_strrcasestr (line_text, *lines);
	}
	else
	{


		if (g_utf8_caselessnmatch (line_text, *lines, strlen (line_text),
					   strlen (*lines)))
			found = line_text;
		else
			found = NULL;
	}

	if (found == NULL)
	{
		g_free (line_text);
		return FALSE;
	}


	offset = g_utf8_strlen (line_text, found - line_text);

	forward_chars_with_skipping (&next, offset, visible_only, !slice, FALSE);


	if (match_start)
	{
		*match_start = next;
	}


	forward_chars_with_skipping (&next, g_utf8_strlen (*lines, -1), visible_only, !slice, TRUE);

	g_free (line_text);

	++lines;

	if (match_end)
		*match_end = next;


	return lines_match (&next, lines, visible_only,
			    slice, NULL, match_end);
}
