sis_check_state(void *driver_data, void *device_data,
			    CardState *state, DFBAccelerationMask accel)
{
	(void)driver_data;
	(void)device_data;

	switch (state->destination->config.format) {
	case DSPF_LUT8:
	case DSPF_ARGB1555:
	case DSPF_RGB16:
	case DSPF_RGB32:
	case DSPF_ARGB:
		break;
	default:
		return;
	}

	if (DFB_DRAWING_FUNCTION(accel)) {
		if (state->drawingflags & ~SIS_SUPPORTED_DRAWING_FLAGS)
			return;
		if (accel & DFXL_FILLTRIANGLE) {

			state->accel = 0;
			return;
		}
		state->accel |= SIS_SUPPORTED_DRAWING_FUNCTIONS;
	}
	else {
		if (state->blittingflags & ~SIS_SUPPORTED_BLITTING_FLAGS)
			return;

		switch (state->source->config.format) {
		case DSPF_LUT8:
		case DSPF_RGB16:
			break;
		default:
			return;
		}

		if (state->source->config.format != state->destination->config.format)
			return;

		state->accel |= SIS_SUPPORTED_BLITTING_FUNCTIONS;
	}
}
