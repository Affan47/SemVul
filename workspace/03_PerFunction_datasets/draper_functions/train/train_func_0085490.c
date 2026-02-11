remove_last_tempo_with_pulses(smf_t *smf, size_t pulses)
{
	smf_tempo_t *tempo;


	if (smf->tempo_array->len == 0)
		return;

	tempo = smf_get_last_tempo(smf);


	if (tempo->time_pulses != pulses)
		return;

	memset(tempo, 0, sizeof(smf_tempo_t));
	free(tempo);

	g_ptr_array_remove_index(smf->tempo_array, smf->tempo_array->len - 1);
}
