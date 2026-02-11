move_to_first_char (GtkTextView *text_view,
                    GtkTextIter *iter,
                    gboolean     display_line)
{
	GtkTextIter last;

	last = *iter;

	if (display_line)
	{
		gtk_text_view_backward_display_line_start (text_view, iter);
		gtk_text_view_forward_display_line_end (text_view, &last);
	}
	else
	{
		gtk_text_iter_set_line_offset (iter, 0);

		if (!gtk_text_iter_ends_line (&last))
		{
			gtk_text_iter_forward_to_line_end (&last);
		}
	}


	while (gtk_text_iter_compare (iter, &last) < 0)
	{
		gunichar c;

		c = gtk_text_iter_get_char (iter);

		if (g_unichar_isspace (c))
		{
			if (!gtk_text_iter_forward_visible_cursor_position (iter))
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
}
