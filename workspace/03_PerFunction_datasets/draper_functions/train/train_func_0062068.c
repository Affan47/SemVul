to_cea_slot(int ordered_ca, unsigned char pos)
{
	int mask = to_spk_mask(pos);
	int i;

	if (mask) {
		for (i = 0; i < 8; i++) {
			if (channel_allocations[ordered_ca].speakers[7 - i] == mask)
				return i;
		}
	}

	return -1;
}
