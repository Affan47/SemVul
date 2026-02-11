fluid_synth_tuning_dump(fluid_synth_t* synth, int bank, int prog,
                        char* name, int len, double* pitch)
{
	fluid_tuning_t* tuning;

	fluid_return_val_if_fail (synth != NULL, FLUID_FAILED);
	fluid_synth_api_enter(synth);

	tuning = fluid_synth_get_tuning (synth, bank, prog);

	if (tuning) {
		if (name) {
			snprintf (name, len - 1, "%s", fluid_tuning_get_name (tuning));
			name[len - 1] = 0;
		}

		if (pitch)
			FLUID_MEMCPY (pitch, fluid_tuning_get_all (tuning), 128 * sizeof (double));
	}

	FLUID_API_RETURN(tuning ? FLUID_OK : FLUID_FAILED);
}
