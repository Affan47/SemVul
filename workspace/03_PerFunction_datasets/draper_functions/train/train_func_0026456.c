sony_nc_battery_care_limit_show(struct device *dev,
		struct device_attribute *attr, char *buffer)
{
	unsigned int result, status;

	if (sony_call_snc_handle(bcare_ctl->handle, 0x0000, &result))
		return -EIO;

	status = (result & 0x01) ? ((result & 0x30) >> 0x04) : 0;
	switch (status) {
	case 1:
		status = 80;
		break;
	case 2:
		status = 50;
		break;
	case 3:
		status = 100;
		break;
	default:
		status = 0;
		break;
	}

	return snprintf(buffer, PAGE_SIZE, "%d\n", status);
}
