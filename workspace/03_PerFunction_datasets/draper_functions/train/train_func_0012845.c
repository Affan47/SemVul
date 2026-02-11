cvt_from_vref_idx(unsigned int vref_caps, unsigned int idx)
{
	unsigned int i, n = 0;

	for (i = 0; i < NUM_VREFS; i++) {
		if (i == idx)
			return n;
		if (vref_caps & (1 << i))
			n++;
	}
	return 0;
}
