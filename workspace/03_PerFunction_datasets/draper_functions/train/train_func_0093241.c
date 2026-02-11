print_song(const struct mpd_song *song)
{
	LOG_INFO("uri: %s\n", mpd_song_get_uri(song));
	print_tag(song, MPD_TAG_ARTIST, "artist");
	print_tag(song, MPD_TAG_ALBUM, "album");
	print_tag(song, MPD_TAG_TITLE, "title");
	print_tag(song, MPD_TAG_TRACK, "track");
	print_tag(song, MPD_TAG_NAME, "name");
	print_tag(song, MPD_TAG_DATE, "date");

	if (mpd_song_get_duration(song) > 0)
		LOG_INFO("time: %i", mpd_song_get_duration(song));

	LOG_INFO("pos: %u", mpd_song_get_pos(song));
}
