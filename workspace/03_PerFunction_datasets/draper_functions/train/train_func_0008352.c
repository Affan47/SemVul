__ctrl_set_metering(struct fimc_is *is, unsigned int value)
{
	unsigned int val;

	switch (value) {
	case V4L2_EXPOSURE_METERING_AVERAGE:
		val = ISP_METERING_COMMAND_AVERAGE;
		break;
	case V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
		val = ISP_METERING_COMMAND_CENTER;
		break;
	case V4L2_EXPOSURE_METERING_SPOT:
		val = ISP_METERING_COMMAND_SPOT;
		break;
	case V4L2_EXPOSURE_METERING_MATRIX:
		val = ISP_METERING_COMMAND_MATRIX;
		break;
	default:
		return -EINVAL;
	}

	__is_set_isp_metering(is, IS_METERING_CONFIG_CMD, val);
	return 0;
}
