lookup_device_info(unsigned short did)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(supported_devices); i++) {
		if (supported_devices[i].did == did) {
			BUG_ON(supported_devices[i].device_info == NULL);
			return supported_devices[i].device_info;
		}
	}

	return NULL;
}
