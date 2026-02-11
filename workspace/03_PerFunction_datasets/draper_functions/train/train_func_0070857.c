fluid_synth_modulate_voices_LOCAL(fluid_synth_t* synth, int chan, int is_cc, int ctrl)
{
	fluid_voice_t* voice;
	int i;

	for (i = 0; i < synth->polyphony; i++) {
		voice = synth->voice[i];

		if (voice->chan == chan)
			fluid_voice_modulate(voice, is_cc, ctrl);
	}
	return FLUID_OK;
}
