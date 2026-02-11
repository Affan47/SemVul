hdhomerun_device_create(uint32_t device_id, uint32_t device_ip, unsigned int tuner, struct hdhomerun_debug_t *dbg)
{
	struct hdhomerun_device_t *hd = (struct hdhomerun_device_t *)calloc(1, sizeof(struct hdhomerun_device_t));
	if (!hd) {
		hdhomerun_debug_printf(dbg, "hdhomerun_device_create: failed to allocate device object\n");
		return NULL;
	}

	hd->dbg = dbg;

	if ((device_id == 0) && (device_ip == 0) && (tuner == 0)) {
		return hd;
	}

	if (hdhomerun_device_set_device(hd, device_id, device_ip) <= 0) {
		free(hd);
		return NULL;
	}
	if (hdhomerun_device_set_tuner(hd, tuner) <= 0) {
		free(hd);
		return NULL;
	}

	return hd;
}
