refresh_range (GtkSourceContextEngine *ce,
	       const GtkTextIter      *start,
	       const GtkTextIter      *end)
{
	GtkTextIter real_end;

	if (gtk_text_iter_equal (start, end))
		return;


	refresh_context_classes (ce, start, end);


	real_end = *end;
	if (gtk_text_iter_starts_line (&real_end))
	{


		gtk_text_iter_backward_cursor_position (&real_end);
	}

	g_signal_emit_by_name (ce->priv->buffer,
			       "highlight_updated",
			       start,
			       &real_end);
}
