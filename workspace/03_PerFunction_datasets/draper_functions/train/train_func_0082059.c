fluid_synth_count_effects_channels(fluid_synth_t* synth)
{
	int result;
	fluid_return_val_if_fail (synth != NULL, 0);
	fluid_synth_api_enter(synth);

	result = synth->effects_channels;
	FLUID_API_RETURN(result);
}
