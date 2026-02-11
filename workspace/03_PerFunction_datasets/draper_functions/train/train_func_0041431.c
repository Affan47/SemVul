_freeze_time(sfx_state_t *self)
{

	GTimeVal ctime;
	long delta;

	song_t *song = self->song;
	sci_get_current_time(&ctime);

	while (song) {
		delta = time_minus(song->wakeup_time, ctime);
		if (delta < 0)
			delta = 0;

		song->delay = delta;

		song = song->next_playing;
	}
}
