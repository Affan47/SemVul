queue_pos_matches(guint queue_pos, const gchar *fname, gint pos)
{
	if (queue_pos < g_queue_get_length(navigation_queue))
	{
		filepos *fpos = g_queue_peek_nth(navigation_queue, queue_pos);

		return (utils_str_equal(fpos->file, fname) && fpos->pos == pos);
	}
	return FALSE;
}
