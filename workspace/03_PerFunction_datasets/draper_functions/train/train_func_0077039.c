mpd_song_new(const char *uri)
{
	struct mpd_song *song;

	assert(uri != NULL);
	assert(mpd_verify_uri(uri));

	song = malloc(sizeof(*song));
	if (song == NULL)

		return NULL;

	song->uri = strdup(uri);
	if (song->uri == NULL) {
		free(song);
		return NULL;
	}

	for (unsigned i = 0; i < MPD_TAG_COUNT; ++i)
		song->tags[i].value = NULL;

	song->duration = 0;
	song->start = 0;
	song->end = 0;
	song->last_modified = 0;
	song->pos = 0;
	song->id = 0;

#ifndef NDEBUG
	song->finished = false;
#endif

	return song;
}
