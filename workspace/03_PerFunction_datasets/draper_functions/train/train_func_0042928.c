mix_to(int **sample_data, int **temp_data, int num_samples, int num_channels)
{
	CL_MutexSection mutex_lock(&mutex);


	int chan;
	for (chan = 0; chan < num_channels; chan++)
	{
		memset(temp_data[chan], 0, sizeof(int) * num_samples);
	}


	double speed = (provider_session->get_frequency() / double(output->mixing_frequency)) * double(speedfactor);
	for (int i = 0; i < num_samples; i++)
	{
		if (buffer_position < buffer_samples_written)
		{
			for (int chan = 0; chan < num_buffer_channels; chan++)
			{
				temp_data[chan][i] = buffer_data[chan][int(buffer_position)];
			}
		}
		else
		{
			if (provider_session->eof())
			{
				playing = false;
				break;
			}


			buffer_position -= buffer_samples_written;
			get_data();
			i--;
			continue;
		}

		buffer_position += speed;
	}


	for (std::vector<CL_SoundFilter *>::size_type index_filter = 0; index_filter < filters.size(); index_filter++)
	{
		filters[index_filter]->filter(temp_data, num_samples, num_buffer_channels);
	}


	int channel_volume[2] = { int (128-pan*128), int (128+pan*128) };
	if (channel_volume[0] < 0) channel_volume[0] = 0;
	if (channel_volume[0] > 128) channel_volume[0] = 128;
	if (channel_volume[1] < 0) channel_volume[1] = 0;
	if (channel_volume[1] > 128) channel_volume[1] = 128;
	int vol = (int) (volume*128);
	channel_volume[0] *= vol;
	channel_volume[1] *= vol;


	if (num_buffer_channels == 1)
	{

		for (int chan = 0; chan < num_channels; chan++)
		{
			for (int i = 0; i < num_samples; i++)
			{
				sample_data[chan][i] += temp_data[0][i]*channel_volume[chan]/16384;
			}
		}
	}
	else
	{
		if (num_channels > num_buffer_channels) num_channels = num_buffer_channels;

		for (int chan = 0; chan < num_channels; chan++)
		{
			for (int i = 0; i < num_samples; i++)
			{
				sample_data[chan][i] += temp_data[chan][i]*channel_volume[chan]/16384;
			}
		}
	}

	return playing;
}
