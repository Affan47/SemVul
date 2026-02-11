smf_get_length_seconds(const smf_t *smf)
{
	int i;
	double seconds = 0.0;

	for (i = 1; i <= smf->number_of_tracks; i++) {
		smf_track_t *track;
		smf_event_t *event;

	       	track = smf_get_track_by_number(smf, i);
		assert(track);

		event = smf_track_get_last_event(track);

		if (event == NULL)
			continue;

		if (event->time_seconds > seconds)
			seconds = event->time_seconds;
	}

	return (seconds);
}
