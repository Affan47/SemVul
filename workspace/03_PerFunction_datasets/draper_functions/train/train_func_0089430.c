fluid_synth_pitch_wheel_sens(fluid_synth_t* synth, int chan, int val)
{
	int result;
	fluid_return_val_if_fail (val >= 0 && val <= 72, FLUID_FAILED);
	FLUID_API_ENTRY_CHAN(FLUID_FAILED);

	if (synth->verbose)
		FLUID_LOG(FLUID_INFO, "pitchsens\t%d\t%d", chan, val);

	fluid_channel_set_pitch_wheel_sensitivity (synth->channel[chan], val);

	result = fluid_synth_update_pitch_wheel_sens_LOCAL (synth, chan);
	FLUID_API_RETURN(result);
}
