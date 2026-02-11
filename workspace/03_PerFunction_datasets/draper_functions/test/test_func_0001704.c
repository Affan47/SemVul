hdmi_manual_channel_allocation(int chs, unsigned char *map)
{
	int i, spks = 0, spk_mask = 0;

	for (i = 0; i < chs; i++) {
		int mask = to_spk_mask(map[i]);
		if (mask) {
			spk_mask |= mask;
			spks++;
		}
	}

	for (i = 0; i < ARRAY_SIZE(channel_allocations); i++) {
		if ((chs == channel_allocations[i].channels ||
		     spks == channel_allocations[i].channels) &&
		    (spk_mask & channel_allocations[i].spk_mask) ==
				channel_allocations[i].spk_mask)
			return channel_allocations[i].ca_index;
	}
	return -1;
}
