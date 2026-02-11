bgpio_multiple_get_masks(struct bgpio_chip *bgc,
				     unsigned long *mask, unsigned long *bits,
				     unsigned long *set_mask,
				     unsigned long *clear_mask)
{
	int i;

	*set_mask = 0;
	*clear_mask = 0;

	for (i = 0; i < bgc->bits; i++) {
		if (*mask == 0)
			break;
		if (__test_and_clear_bit(i, mask)) {
			if (test_bit(i, bits))
				*set_mask |= bgc->pin2mask(bgc, i);
			else
				*clear_mask |= bgc->pin2mask(bgc, i);
		}
	}
}
