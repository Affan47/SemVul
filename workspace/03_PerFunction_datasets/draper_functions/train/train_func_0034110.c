fluid_rvoice_calc_amp(fluid_rvoice_t* voice)
{
	fluid_real_t target_amp;

	if (fluid_adsr_env_get_section(&voice->envlfo.volenv) == FLUID_VOICE_ENVDELAY)
		return -1;

	if (fluid_adsr_env_get_section(&voice->envlfo.volenv) == FLUID_VOICE_ENVATTACK) {


		target_amp = fluid_atten2amp (voice->dsp.attenuation)
		             * fluid_cb2amp (fluid_lfo_get_val(&voice->envlfo.modlfo) * -voice->envlfo.modlfo_to_vol)
		             * fluid_adsr_env_get_val(&voice->envlfo.volenv);
	} else {
		fluid_real_t amplitude_that_reaches_noise_floor;
		fluid_real_t amp_max;

		target_amp = fluid_atten2amp (voice->dsp.attenuation)
		             * fluid_cb2amp (960.0f * (1.0f - fluid_adsr_env_get_val(&voice->envlfo.volenv))
		                             + fluid_lfo_get_val(&voice->envlfo.modlfo) * -voice->envlfo.modlfo_to_vol);


		if (voice->dsp.has_looped)
			amplitude_that_reaches_noise_floor = voice->dsp.amplitude_that_reaches_noise_floor_loop;
		else
			amplitude_that_reaches_noise_floor = voice->dsp.amplitude_that_reaches_noise_floor_nonloop;


		amp_max = fluid_atten2amp (voice->dsp.min_attenuation_cB) *
		          fluid_adsr_env_get_val(&voice->envlfo.volenv);


		if (amp_max < amplitude_that_reaches_noise_floor) {
			return 0;
		}
	}


	voice->dsp.amp_incr = (target_amp - voice->dsp.amp) / FLUID_BUFSIZE;

	fluid_check_fpe ("voice_write amplitude calculation");


	if ((voice->dsp.amp == 0.0f) && (voice->dsp.amp_incr == 0.0f))
		return -1;

	return 1;
}
