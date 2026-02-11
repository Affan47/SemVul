new_tempo(smf_t *smf, size_t pulses)
{
	smf_tempo_t *tempo, *previous_tempo = NULL;

	if (smf->tempo_array->len > 0) {
		previous_tempo = smf_get_last_tempo(smf);


		if (previous_tempo->time_pulses == pulses)
			return (previous_tempo);
	}

	tempo = malloc(sizeof(smf_tempo_t));
	if (tempo == NULL) {
		g_critical("Cannot allocate smf_tempo_t.");
		return (NULL);
	}

	tempo->time_pulses = pulses;

	if (previous_tempo != NULL) {
		tempo->microseconds_per_quarter_note = previous_tempo->microseconds_per_quarter_note;
		tempo->numerator = previous_tempo->numerator;
		tempo->denominator = previous_tempo->denominator;
		tempo->clocks_per_click = previous_tempo->clocks_per_click;
		tempo->notes_per_note = previous_tempo->notes_per_note;
	} else {
		tempo->microseconds_per_quarter_note = 500000;
		tempo->numerator = 4;
		tempo->denominator = 4;
		tempo->clocks_per_click = -1;
		tempo->notes_per_note = -1;
	}

	g_ptr_array_add(smf->tempo_array, tempo);

	if (pulses == 0)
		tempo->time_seconds = 0.0;
	else
		tempo->time_seconds = seconds_from_pulses(smf, pulses);

	return (tempo);
}
