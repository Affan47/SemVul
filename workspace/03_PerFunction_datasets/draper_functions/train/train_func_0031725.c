mpd_song_checksum(const mpd_Song * song)
{
	gchar *retv = NULL;
	if (song)
	{
		GChecksum *cs = g_checksum_new(G_CHECKSUM_SHA256);
		if (song->file)
			g_checksum_update(cs, (guchar *) song->file, -1);
		if (song->artist)
			g_checksum_update(cs, (guchar *) song->artist, -1);
		if (song->title)
			g_checksum_update(cs, (guchar *) song->title, -1);
		if (song->album)
			g_checksum_update(cs, (guchar *) song->album, -1);
		if (song->track)
			g_checksum_update(cs, (guchar *) song->track, -1);
		if (song->name)
			g_checksum_update(cs, (guchar *) song->name, -1);
		if (song->date)
			g_checksum_update(cs, (guchar *) song->date, -1);
		if (song->genre)
			g_checksum_update(cs, (guchar *) song->genre, -1);
		if (song->composer)
			g_checksum_update(cs, (guchar *) song->composer, -1);
		if (song->performer)
			g_checksum_update(cs, (guchar *) song->performer, -1);
		if (song->disc)
			g_checksum_update(cs, (guchar *) song->disc, -1);
		if (song->albumartist)
			g_checksum_update(cs, (guchar *) song->albumartist, -1);

		retv = g_strdup(g_checksum_get_string(cs));
		g_checksum_free(cs);
	}
	return retv;
}
