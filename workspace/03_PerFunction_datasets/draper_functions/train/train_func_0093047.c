__is_hw_update_params(struct fimc_is *is)
{
	unsigned long *p_index;
	int i, id, ret = 0;

	id = is->config_index;
	p_index = &is->config[id].p_region_index[0];

	if (test_bit(PARAM_GLOBAL_SHOTMODE, p_index))
		__fimc_is_hw_update_param_global_shotmode(is);

	if (test_bit(PARAM_SENSOR_FRAME_RATE, p_index))
		__fimc_is_hw_update_param_sensor_framerate(is);

	for (i = PARAM_ISP_CONTROL; i < PARAM_DRC_CONTROL; i++) {
		if (test_bit(i, p_index))
			ret = __fimc_is_hw_update_param(is, i);
	}

	for (i = PARAM_DRC_CONTROL; i < PARAM_SCALERC_CONTROL; i++) {
		if (test_bit(i, p_index))
			ret = __fimc_is_hw_update_param(is, i);
	}

	for (i = PARAM_FD_CONTROL; i <= PARAM_FD_CONFIG; i++) {
		if (test_bit(i, p_index))
			ret = __fimc_is_hw_update_param(is, i);
	}

	return ret;
}
