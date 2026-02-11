process(jack_nframes_t nframes, void *arg)
{
	int i,j;
	void* port_buf = jack_port_get_buffer(output_port, nframes);
	unsigned char* buffer;
	jack_midi_clear_buffer(port_buf);


	for(i=0; i<nframes; i++)
	{
		for(j=0; j<num_notes; j++)
		{
			if(note_starts[j] == loop_index)
			{
				buffer = jack_midi_event_reserve(port_buf, i, 3);

				buffer[2] = 64;
				buffer[1] = note_frqs[j];
				buffer[0] = 0x90;
			}
			else if(note_starts[j] + note_lengths[j] == loop_index)
			{
				buffer = jack_midi_event_reserve(port_buf, i, 3);

				buffer[2] = 64;
				buffer[1] = note_frqs[j];
				buffer[0] = 0x80;
			}
		}
		loop_index = loop_index+1 >= loop_nsamp ? 0 : loop_index+1;
	}
	return 0;
}
