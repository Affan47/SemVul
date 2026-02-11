_reset_synth_channels(base_song_iterator_t *self, song_iterator_channel_t *channel)
{
	int i;
	byte buf[5];
	tell_synth_func *tell = sfx_get_player_tell_func();

	for (i = 0; i < MIDI_CHANNELS; i++)
	{
		if (channel->saw_notes & (1 << i))
		{
			buf[0] = 0xe0 | i;
			buf[1] = 0x80;
			buf[2] = 0x40;
			if (tell)
				tell(3, buf);

		}
	}
}
