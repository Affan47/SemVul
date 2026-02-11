fluid_voice_optimize_sample(fluid_sample_t* s)
{
	signed short peak_max = 0;
	signed short peak_min = 0;
	signed short peak;
	fluid_real_t normalized_amplitude_during_loop;
	double result;
	int i;


	if (!s->valid) return (FLUID_OK);

	if (!s->amplitude_that_reaches_noise_floor_is_valid) {

		for (i = (int)s->loopstart; i < (int) s->loopend; i ++) {
			signed short val = s->data[i];
			if (val > peak_max) {
				peak_max = val;
			} else if (val < peak_min) {
				peak_min = val;
			}
		}


		if (peak_max >- peak_min) {
			peak = peak_max;
		} else {
			peak =- peak_min;
		};
		if (peak == 0) {

			peak = 1;
		};


		normalized_amplitude_during_loop = ((fluid_real_t)peak)/32768.;
		result = FLUID_NOISE_FLOOR / normalized_amplitude_during_loop;


		s->amplitude_that_reaches_noise_floor = (double)result;
		s->amplitude_that_reaches_noise_floor_is_valid = 1;
#if 0
		printf("Sample peak detection: factor %f\n", (double)result);
#endif
	};
	return FLUID_OK;
}
