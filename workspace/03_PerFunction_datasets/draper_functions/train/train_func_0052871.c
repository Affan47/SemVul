fluid_synth_start_voice(fluid_synth_t* synth, fluid_voice_t* voice)
{
	fluid_return_if_fail (synth != NULL);
	fluid_return_if_fail (voice != NULL);

	fluid_synth_api_enter(synth);


	fluid_synth_kill_by_exclusive_class_LOCAL(synth, voice);

	fluid_voice_start(voice);
	if (synth->eventhandler->is_threadsafe)
		fluid_voice_lock_rvoice(voice);
	fluid_rvoice_eventhandler_add_rvoice(synth->eventhandler, voice->rvoice);
	fluid_synth_api_exit(synth);
}
