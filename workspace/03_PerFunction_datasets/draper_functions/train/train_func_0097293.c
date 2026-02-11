stream_init_multi(int channels,const char **names,const int *default_mixing_levels,
		int sample_rate,
		int param,void (*callback)(int param,INT16 **buffer,int length))
{
	int channel,i;


	channel = mixer_allocate_channels(channels,default_mixing_levels);

	stream_joined_channels[channel] = channels;

	for (i = 0;i < channels;i++)
	{
		mixer_set_name(channel+i,names[i]);

		if ((stream_buffer[channel+i] = malloc(sizeof(INT16)*BUFFER_LEN)) == 0)
			return -1;

		stream_sample_rate[channel+i] = sample_rate;
		stream_buffer_pos[channel+i] = 0;
		if (sample_rate)
			stream_sample_length[channel+i] = 1000000 / sample_rate;
		else
			stream_sample_length[channel+i] = 0;
	}

	stream_param[channel] = param;
	stream_callback_multi[channel] = callback;
	set_RC_filter(channel,0,0,0,0);

	return channel;
}
