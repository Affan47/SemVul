s5c73m3_set_power_line_freq(struct s5c73m3 *state, int val)
{
	unsigned int pwr_line_freq = COMM_FLICKER_NONE;

	switch (val) {
	case V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
		pwr_line_freq = COMM_FLICKER_NONE;
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
		pwr_line_freq = COMM_FLICKER_AUTO_50HZ;
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
		pwr_line_freq = COMM_FLICKER_AUTO_60HZ;
		break;
	default:
	case V4L2_CID_POWER_LINE_FREQUENCY_AUTO:
		pwr_line_freq = COMM_FLICKER_NONE;
	}

	return s5c73m3_isp_command(state, COMM_FLICKER_MODE, pwr_line_freq);
}
