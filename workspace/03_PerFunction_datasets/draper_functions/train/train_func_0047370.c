count_checksum(struct sun_disklabel *label)
{
	uint16_t *ptr = ((uint16_t *) (label + 1)) - 1;
	uint16_t sum;

	for (sum = 0; ptr >= ((uint16_t *) label);)
		sum ^= *ptr--;

	return sum;
}
