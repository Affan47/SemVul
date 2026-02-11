fluid_synth_stop_LOCAL (fluid_synth_t *synth, unsigned int id)
{
	fluid_voice_t* voice;
	int i;

	for (i = 0; i < synth->polyphony; i++) {
		voice = synth->voice[i];

		if (_ON(voice) && (fluid_voice_get_id (voice) == id))
			fluid_voice_noteoff(voice);
	}
}
