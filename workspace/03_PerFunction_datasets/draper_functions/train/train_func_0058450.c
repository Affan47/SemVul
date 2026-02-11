tracker_db_journal_get_rotating (gboolean *do_rotating,
                                 gsize    *chunk_size,
                                 gchar   **rotate_to)
{
	*do_rotating = rotating_settings.do_rotating;
	*chunk_size = rotating_settings.chunk_size;
	if (rotating_settings.rotate_to) {
		*rotate_to = g_strdup (rotating_settings.rotate_to);
	} else {
		*rotate_to = NULL;
	}
}
