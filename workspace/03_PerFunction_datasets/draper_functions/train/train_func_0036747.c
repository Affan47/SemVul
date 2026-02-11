_blot_mask(bitstr_t *mask, uint16_t blot)
{
	uint16_t i, size = 0;
	int prev = -1;

	if (!mask)
		return;
	size = bit_size(mask);
	for (i = 0; i < size; i++) {
		if (bit_test(mask, i)) {

			uint16_t start = (i / blot) * blot;
			if (start != prev) {
				bit_nset(mask, start, start+blot-1);
				prev = start;
			}
		}
	}
}
