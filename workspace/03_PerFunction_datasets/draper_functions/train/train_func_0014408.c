invalidate_region (GtkSourceContextEngine *ce,
		   gint                    offset,
		   gint                    length)
{
	InvalidRegion *region = &ce->priv->invalid_region;
	GtkTextBuffer *buffer = ce->priv->buffer;
	GtkTextIter iter;
	gint end_offset;

	end_offset = length >= 0 ? offset + length : offset;

	if (region->empty)
	{
		region->empty = FALSE;
		region->delta = length;

		gtk_text_buffer_get_iter_at_offset (buffer, &iter, offset);
		gtk_text_buffer_move_mark (buffer, region->start, &iter);

		gtk_text_iter_set_offset (&iter, end_offset);
		gtk_text_buffer_move_mark (buffer, region->end, &iter);
	}
	else
	{
		gtk_text_buffer_get_iter_at_mark (buffer, &iter, region->start);

		if (gtk_text_iter_get_offset (&iter) > offset)
		{
			gtk_text_iter_set_offset (&iter, offset);
			gtk_text_buffer_move_mark (buffer, region->start, &iter);
		}

		gtk_text_buffer_get_iter_at_mark (buffer, &iter, region->end);

		if (gtk_text_iter_get_offset (&iter) < end_offset)
		{
			gtk_text_iter_set_offset (&iter, end_offset);
			gtk_text_buffer_move_mark (buffer, region->end, &iter);
		}

		region->delta += length;
	}

	DEBUG (({
		gint start, end;
		gtk_text_buffer_get_iter_at_mark (buffer, &iter, region->start);
		start = gtk_text_iter_get_offset (&iter);
		gtk_text_buffer_get_iter_at_mark (buffer, &iter, region->end);
		end = gtk_text_iter_get_offset (&iter);
		g_assert (start <= end - region->delta);
	}));

	CHECK_TREE (ce);

	install_first_update (ce);
}
