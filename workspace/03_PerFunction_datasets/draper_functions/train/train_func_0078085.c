fluid_synth_set_tuning_LOCAL (fluid_synth_t *synth, int chan,
                              fluid_tuning_t *tuning, int apply)
{
	fluid_tuning_t *old_tuning;
	fluid_channel_t *channel;

	channel = synth->channel[chan];

	old_tuning = fluid_channel_get_tuning (channel);
	fluid_channel_set_tuning (channel, tuning);

	if (apply) fluid_synth_update_voice_tuning_LOCAL (synth, channel);


	if (old_tuning) {
		fluid_tuning_unref (old_tuning, 1);
	}


	return FLUID_OK;
}
