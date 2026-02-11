fluid_synth_set_polyphony(fluid_synth_t* synth, int polyphony)
{
	int result;
	fluid_return_val_if_fail (synth != NULL, FLUID_FAILED);
	fluid_return_val_if_fail (polyphony >= 1 && polyphony <= 65535, FLUID_FAILED);
	fluid_synth_api_enter(synth);

	result = fluid_synth_update_polyphony_LOCAL(synth, polyphony);

	FLUID_API_RETURN(result);
}
