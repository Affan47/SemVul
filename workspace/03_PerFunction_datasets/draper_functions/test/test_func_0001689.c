track_info_set_title (TrackInfo  *track,
		      const char *title)
{
	if (title == NULL) {
		g_free (track->title);
		track->title = g_strdup_printf (_("Track %u"), track->number + 1);
		return;
	}

	if (title == track->title)
		return;

	g_free (track->title);
	track->title = g_strdup (title);
}
