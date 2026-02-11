mixer_stop_sample(int ch)
{
	struct mixer_channel_data *channel = &mixer_channel[ch];

	mixerlogerror(("Mixer:mixer_stop_sample(%s)\n",channel->name));

	mixer_update_channel(channel, sound_scalebufferpos(samples_this_frame));

	if (channel->is_playing) {
		channel->is_playing = 0;
		mixer_flush(channel);
	}
}
