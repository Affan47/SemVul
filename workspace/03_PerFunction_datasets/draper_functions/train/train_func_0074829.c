on_gnupg_source_check (GSource *source)
{
	GnupgSource *gnupg_source = (GnupgSource*)source;
	gint i;

	for (i = 0; i < NUM_FDS; ++i) {
		if (gnupg_source->polls[i].fd >= 0 && gnupg_source->polls[i].revents != 0)
			return TRUE;
	}
	return FALSE;
}
