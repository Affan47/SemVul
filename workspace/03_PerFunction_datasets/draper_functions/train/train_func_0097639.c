hdhomerun_device_selector_find_device(struct hdhomerun_device_selector_t *hds, uint32_t device_id, unsigned int tuner_index)
{
	size_t index;
	for (index = 0; index < hds->hd_count; index++) {
		struct hdhomerun_device_t *entry = hds->hd_list[index];
		if (hdhomerun_device_get_device_id(entry) != device_id) {
			continue;
		}
		if (hdhomerun_device_get_tuner(entry) != tuner_index) {
			continue;
		}
		return entry;
	}

	return NULL;
}
