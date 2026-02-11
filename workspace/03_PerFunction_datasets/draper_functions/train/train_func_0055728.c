sd_get_phase_len(u32 phase_map, unsigned int start_bit)
{
	int i;

	for (i = 0; i < RTSX_PHASE_MAX; i++) {
		if (test_phase_bit(phase_map, start_bit + i) == 0)
			return i;
	}
	return RTSX_PHASE_MAX;
}
