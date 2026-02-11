mixer_set_lowpass_frequency(int ch, int freq)
{
	struct mixer_channel_data *channel = &mixer_channel[ch];

	assert(!channel->is_playing && !channel->is_stream);

	mixerlogerror(("Mixer:mixer_set_lowpass_frequency(%s,%d)\n",channel->name,freq));

	channel->request_lowpass_frequency = freq;
}
