viapadlock_rng_enable(unsigned int enable, viapadlock_rng_config_t* cfg)
{
	int error;
	int i;
	uint32_t buf[2];

	if (!viapadlock_engines_detected) {
		errno = ENXIO;
		return -1;
	}

	if (cfg) {

		if (cfg->dc_bias > VIA1_DCBIAS_MAX)
			cfg->dc_bias = VIA1_DCBIAS_MAX;
		if (cfg->string_filter && cfg->string_filter < VIA1_STRFILT_MIN)
			cfg->string_filter = VIA1_STRFILT_MIN;
		if (cfg->string_filter > VIA1_STRFILT_MAX)
			cfg->string_filter = VIA1_STRFILT_MAX;

		viapadlock_state.MSR_LSW =
			(((cfg->whitener)? 0 : VIA1_RAWBITS_ENABLE) |
			(cfg->dc_bias << VIA1_DCBIAS_SHIFT) |
			(cfg->noise_source << VIA1_NOISE_SRC_SHIFT) |
			((cfg->string_filter > 0)?
			     VIA1_STRFILT_ENABLE |
			      (cfg->string_filter << VIA1_STRFILT_CNT_SHIFT) :
			     0) |
			VIA1_RNG_ENABLE) & viapadlock_state.MSR_LSW_MASK;
		viapadlock_state.divisor = cfg->divisor;
	} else if (!viapadlock_state.MSR_LSW) {

		errno = EINVAL;
		return -1;
	}

	buf[0] = viapadlock_state.MSR_LSW;
	if (!enable) buf[0] &= ~VIA1_RNG_ENABLE;

	buf[1] = 0;
	error = 0;
	for (i = 0; i < viapadlock_engines_detected; i++) {
		if ((lseek(viapadlock_state.msr_fd[i], MSR_VIA_RNG1, SEEK_SET)
		    != MSR_VIA_RNG1) ||
		    (write(viapadlock_state.msr_fd[i], &buf, 8) == -1) ) {
			error = errno;
			break;
		}
	}

	errno = error;
	if (error) return -1;
	return 0;
}
