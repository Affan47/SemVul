m5mols_set_metering_mode(struct m5mols_info *info, int mode)
{
	unsigned int metering;

	switch (mode) {
	case V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
		metering = REG_AE_CENTER;
		break;
	case V4L2_EXPOSURE_METERING_SPOT:
		metering = REG_AE_SPOT;
		break;
	default:
		metering = REG_AE_ALL;
		break;
	}

	return m5mols_write(&info->sd, AE_MODE, metering);
}
