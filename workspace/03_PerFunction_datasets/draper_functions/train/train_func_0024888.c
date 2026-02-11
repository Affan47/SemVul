process_audio (jack_nframes_t nframes)
{
	sample_t *buffer = (sample_t *) jack_port_get_buffer (output_port, nframes);
	jack_nframes_t frames_left = nframes;

	while (wave_length - offset < frames_left) {
		memcpy (buffer + (nframes - frames_left), wave + offset, sizeof (sample_t) * (wave_length - offset));
		frames_left -= wave_length - offset;
		offset = 0;
	}
	if (frames_left > 0) {
		memcpy (buffer + (nframes - frames_left), wave + offset, sizeof (sample_t) * frames_left);
		offset += frames_left;
	}


}
