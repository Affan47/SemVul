gtk_source_buffer_move_cursor (GtkTextBuffer     *buffer,
			       const GtkTextIter *iter,
			       GtkTextMark       *mark)
{
	GtkSourceBuffer *source_buffer;
	GtkTextIter start, end;
	gunichar cursor_char;
	GtkSourceBracketMatchType previous_state;

	g_return_if_fail (GTK_SOURCE_IS_BUFFER (buffer));
	g_return_if_fail (iter != NULL);
	g_return_if_fail (mark != NULL);
	g_return_if_fail (gtk_text_iter_get_buffer (iter) == buffer);

	if (mark != gtk_text_buffer_get_insert (buffer))
		return;

	source_buffer = GTK_SOURCE_BUFFER (buffer);

	if (source_buffer->priv->bracket_match == GTK_SOURCE_BRACKET_MATCH_FOUND)
	{
		gtk_text_buffer_get_iter_at_mark (buffer,
						  &start,
						  source_buffer->priv->bracket_mark_match);

		gtk_text_buffer_get_iter_at_mark (buffer,
						  &end,
						  source_buffer->priv->bracket_mark_cursor);

		gtk_text_iter_order (&start, &end);
		gtk_text_iter_forward_char (&end);
		gtk_text_buffer_remove_tag (buffer,
					    source_buffer->priv->bracket_match_tag,
					    &start,
					    &end);
	}

	if (!source_buffer->priv->highlight_brackets)
		return;

	start = *iter;
	previous_state = source_buffer->priv->bracket_match;
	if (!gtk_source_buffer_find_bracket_match_with_limit (source_buffer,
	                                                      &start,
	                                                      &source_buffer->priv->bracket_match,
	                                                      MAX_CHARS_BEFORE_FINDING_A_MATCH))
	{


		if (previous_state != GTK_SOURCE_BRACKET_MATCH_NONE ||
		    source_buffer->priv->bracket_match != GTK_SOURCE_BRACKET_MATCH_NONE)
		{
			g_signal_emit (source_buffer,
				       buffer_signals[BRACKET_MATCHED],
				       0,
				       &end,
				       source_buffer->priv->bracket_match);
		}
	}
	else
	{
		g_signal_emit (source_buffer,
			       buffer_signals[BRACKET_MATCHED],
			       0,
			       &start,
			       source_buffer->priv->bracket_match);


		source_buffer->priv->allow_bracket_match = TRUE;


		if (!source_buffer->priv->bracket_mark_match)
		{
			source_buffer->priv->bracket_mark_match =
 				gtk_text_buffer_create_mark (buffer,
							     NULL,
							     &start,
							     TRUE);
 		}
 		else
 		{
 			gtk_text_buffer_move_mark (buffer,
						   source_buffer->priv->bracket_mark_match,
						   &start);
 		}

		end = start;
		gtk_text_iter_forward_char (&end);
		gtk_text_buffer_apply_tag (buffer,
					   get_bracket_match_tag (source_buffer),
					   &start,
					   &end);


		start = *iter;
		cursor_char = gtk_text_iter_get_char (&start);
		if (bracket_pair (cursor_char, NULL) == 0)
			gtk_text_iter_backward_char (&start);

		if (!source_buffer->priv->bracket_mark_cursor)
		{
			source_buffer->priv->bracket_mark_cursor =
				gtk_text_buffer_create_mark (buffer,
							     NULL,
							     &start,
							     FALSE);
		}
		else
		{
			gtk_text_buffer_move_mark (buffer,
						   source_buffer->priv->bracket_mark_cursor,
						   &start);
		}

		end = start;
		gtk_text_iter_forward_char (&end);
		gtk_text_buffer_apply_tag (buffer,
					   get_bracket_match_tag (source_buffer),
					   &start,
					   &end);

		source_buffer->priv->allow_bracket_match = FALSE;
	}
}
