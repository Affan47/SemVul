skl_tplg_be_link_type(int dev_type)
{
	int ret;

	switch (dev_type) {
	case SKL_DEVICE_BT:
		ret = NHLT_LINK_SSP;
		break;

	case SKL_DEVICE_DMIC:
		ret = NHLT_LINK_DMIC;
		break;

	case SKL_DEVICE_I2S:
		ret = NHLT_LINK_SSP;
		break;

	case SKL_DEVICE_HDALINK:
		ret = NHLT_LINK_HDA;
		break;

	default:
		ret = NHLT_LINK_INVALID;
		break;
	}

	return ret;
}
