smf_track_get_event_by_number(const smf_track_t *track, size_t event_number)
{
	smf_event_t *event;

	assert(event_number >= 1);

	if (event_number > track->number_of_events)
		return (NULL);

	event = g_ptr_array_index(track->events_array, event_number - 1);

	assert(event);

	return (event);
}
