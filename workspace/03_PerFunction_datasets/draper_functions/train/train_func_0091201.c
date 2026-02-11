mixer_sh_update(void)
{
	struct mixer_channel_data* channel;
	unsigned accum_pos = accum_base;
	INT16 *mix;
	int sample;
	int i;

	profiler_mark(PROFILER_MIXER);


	for (i = 0, channel = mixer_channel; i < first_free_channel; i++, channel++)
	{
		mixer_update_channel(channel, samples_this_frame);


		if (samples_this_frame > channel->samples_available)
			channel->samples_available = 0;
		else
			channel->samples_available -= samples_this_frame;
	}


	if (!is_stereo)
	{
		mix = mix_buffer;
		for (i = 0; i < samples_this_frame; i++)
		{

			sample = left_accum[accum_pos];
         MAME_CLAMP_SAMPLE(sample);


			*mix++ = sample;
			left_accum[accum_pos] = 0;


			accum_pos = (accum_pos + 1) & ACCUMULATOR_MASK;
		}
	}


	else
	{
		mix = mix_buffer;
		for (i = 0; i < samples_this_frame; i++)
		{

			sample = left_accum[accum_pos];
         MAME_CLAMP_SAMPLE(sample);


			*mix++ = sample;
			left_accum[accum_pos] = 0;


			sample = right_accum[accum_pos];
         MAME_CLAMP_SAMPLE(sample);


			*mix++ = sample;
			right_accum[accum_pos] = 0;


			accum_pos = (accum_pos + 1) & ACCUMULATOR_MASK;
		}
	}


	samples_this_frame = osd_update_audio_stream(mix_buffer);

	accum_base = accum_pos;

	profiler_mark(PROFILER_END);
}
