smf_event_length_is_valid(const smf_event_t *event)
{
	assert(event);
	assert(event->midi_buffer);

	int32_t expected;

	if (event->midi_buffer_length < 1)
		return (0);


	if (smf_event_is_sysex(event))
		return (1);


	expected = expected_message_length(event->midi_buffer[0],
			&(event->midi_buffer[1]), event->midi_buffer_length - 1);
	if (expected < 0 || event->midi_buffer_length != (size_t)expected) {
		return (0);
	}

	return (1);
}
