fluid_rampreset_remembervoice (fluid_rampreset_t* preset, fluid_voice_t* voice)
{
	fluid_rampreset_voice_t *presetvoice = FLUID_NEW(fluid_rampreset_voice_t);
	if (presetvoice == NULL) {
		FLUID_LOG(FLUID_ERR, "Out of memory");
		return FLUID_FAILED;
	}

	presetvoice->voice = voice;
	presetvoice->voiceID = fluid_voice_get_id(voice);

	preset->presetvoices = fluid_list_append(preset->presetvoices, (void *)presetvoice);
	if (preset->presetvoices == NULL) {
		FLUID_FREE(presetvoice);
		FLUID_LOG(FLUID_ERR, "Out of memory");
		return FLUID_FAILED;
	}
	return FLUID_OK;
}
