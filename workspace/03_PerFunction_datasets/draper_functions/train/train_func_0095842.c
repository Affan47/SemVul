gedit_document_goto_line_offset (GeditDocument *doc,
				 gint           line,
				 gint           line_offset)
{
	gboolean ret;
	GtkTextIter iter;

	g_return_val_if_fail (GEDIT_IS_DOCUMENT (doc), FALSE);
	g_return_val_if_fail (line >= -1, FALSE);
	g_return_val_if_fail (line_offset >= -1, FALSE);

	ret = gedit_document_goto_line (doc, line);

	if (ret)
	{
		guint offset_count;

		gtk_text_buffer_get_iter_at_line (GTK_TEXT_BUFFER (doc),
						  &iter,
						  line);

		offset_count = gtk_text_iter_get_chars_in_line (&iter);
		if (line_offset > offset_count)
		{
			ret = FALSE;
		}
		else
		{
			gtk_text_iter_set_line_offset (&iter, line_offset);
			gtk_text_buffer_place_cursor (GTK_TEXT_BUFFER (doc), &iter);
		}
	}

	return ret;
}
