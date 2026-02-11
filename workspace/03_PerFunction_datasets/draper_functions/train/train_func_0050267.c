hdhomerun_device_set_tuner_filter_by_array_append(char *ptr, char *end, uint16_t range_begin, uint16_t range_end)
{
	if (range_begin == range_end) {
		return hdhomerun_sprintf(ptr, end, "0x%04x ", (unsigned int)range_begin);
	} else {
		return hdhomerun_sprintf(ptr, end, "0x%04x-0x%04x ", (unsigned int)range_begin, (unsigned int)range_end);
	}
}
