fluid_synth_set_preset (fluid_synth_t *synth, int chan, fluid_preset_t *preset)
{
	fluid_channel_t *channel;

	fluid_return_val_if_fail (synth != NULL, FLUID_FAILED);
	fluid_return_val_if_fail (chan >= 0 && chan < synth->midi_channels, FLUID_FAILED);

	channel = synth->channel[chan];

	return fluid_channel_set_preset (channel, preset);
}
