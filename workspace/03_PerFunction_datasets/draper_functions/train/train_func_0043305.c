write_event_contents(smf_event_t *event)
{
	if (smf_event_is_system_realtime(event) || smf_event_is_system_common(event))
		return (write_escaped_event_contents(event));

	return (track_append(event->track, event->midi_buffer, event->midi_buffer_length));
}
