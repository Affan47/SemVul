hdhomerun_device_set_tuner(struct hdhomerun_device_t *hd, unsigned int tuner)
{
	if (hd->multicast_ip != 0) {
		if (tuner != 0) {
			hdhomerun_debug_printf(hd->dbg, "hdhomerun_device_set_tuner: tuner cannot be specified in multicast mode\n");
			return -1;
		}

		return 1;
	}

	hd->tuner = tuner;
	hdhomerun_sprintf(hd->name, hd->name + sizeof(hd->name), "%08X-%u", (unsigned int)hd->device_id, hd->tuner);

	return 1;
}
