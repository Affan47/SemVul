fluid_channel_set_preset(fluid_channel_t* chan, fluid_preset_t* preset)
{

	fluid_preset_notify (chan->preset, FLUID_PRESET_UNSELECTED, chan->channum);

	if (chan->preset) {
		fluid_sfont_t *sfont;
		sfont = chan->preset->sfont;
		delete_fluid_preset (chan->preset);
		fluid_synth_sfont_unref (chan->synth, sfont);
	}

	chan->preset = preset;

	fluid_preset_notify (preset, FLUID_PRESET_SELECTED, chan->channum);

	return FLUID_OK;
}
