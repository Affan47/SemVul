ReserveEvent(jack_nframes_t time, jack_shmsize_t size)
{
    jack_shmsize_t space = MaxEventSize();
    if (space == 0 || size > space) {
        jack_error("JackMidiBuffer::ReserveEvent - the buffer does not have "
                   "enough room to enqueue a %lu byte event", size);
        lost_events++;
        return 0;
    }
    JackMidiEvent* event = &events[event_count++];
    event->time = time;
    event->size = size;
    if (size <= JackMidiEvent::INLINE_SIZE_MAX) {
        return event->data;
    }

    write_pos += size;
    event->offset = buffer_size - write_pos;
    return (jack_midi_data_t*)this + event->offset;
}
