fluid_synth_api_enter(fluid_synth_t* synth)
{
	if (synth->use_mutex) {
		fluid_rec_mutex_lock(synth->mutex);
	}
	if (!synth->public_api_count) {
		fluid_synth_check_finished_voices(synth);
	}
	synth->public_api_count++;
}
