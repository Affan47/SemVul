read_event(uint32_t* delta_t, uint32_t* size, uint8_t** buf, event_id_t* note_id) const
{
	smf_event_t* event;

	assert(delta_t);
	assert(size);
	assert(buf);
	assert(note_id);

	if ((event = smf_track_get_next_event(_smf_track)) != NULL) {

		*delta_t = event->delta_time_pulses;

		if (smf_event_is_metadata(event)) {
			*note_id = -1;

			if (event->midi_buffer[1] == 0x7f) {

				uint32_t evsize;
				uint32_t lenlen;

				if (smf_extract_vlq (&event->midi_buffer[2], event->midi_buffer_length-2, &evsize, &lenlen) == 0) {

					if (event->midi_buffer[2+lenlen] == 0x99 &&
					    event->midi_buffer[3+lenlen] == 0x1) {

						uint32_t id;
						uint32_t idlen;

						if (smf_extract_vlq (&event->midi_buffer[4+lenlen], event->midi_buffer_length-(4+lenlen), &id, &idlen) == 0) {
							*note_id = id;
						}
					}
				}
			}
			return 0;
		}

		int event_size = event->midi_buffer_length;
		assert(event_size > 0);


		if (*size < (unsigned)event_size) {
			*buf = (uint8_t*)realloc(*buf, event_size);
		}
		memcpy(*buf, event->midi_buffer, size_t(event_size));
		*size = event_size;

		assert(midi_event_is_valid(*buf, *size));


		return event_size;
	} else {
		return -1;
	}
}
