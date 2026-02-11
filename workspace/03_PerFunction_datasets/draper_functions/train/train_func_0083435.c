hdhomerun_device_create_from_str_ip(const char *device_str, struct hdhomerun_debug_t *dbg)
{
	unsigned int a[4];
	unsigned int port = 0;
	unsigned int tuner = 0;

	if (sscanf(device_str, "%u.%u.%u.%u:%u", &a[0], &a[1], &a[2], &a[3], &port) == 5) {
		return hdhomerun_device_create_from_str_ip_result(a, port, tuner, dbg);
	}
	if (sscanf(device_str, "%u.%u.%u.%u-%u", &a[0], &a[1], &a[2], &a[3], &tuner) == 5) {
		return hdhomerun_device_create_from_str_ip_result(a, port, tuner, dbg);
	}
	if (sscanf(device_str, "%u.%u.%u.%u", &a[0], &a[1], &a[2], &a[3]) == 4) {
		return hdhomerun_device_create_from_str_ip_result(a, port, tuner, dbg);
	}

	return NULL;
}
