mem_exists(uint8_t *p)
{
	uint8_t c;

	c = linr8(p);

	linw8(p, 0xaa);
	if (linr8(p) != 0xaa) return 0;
	linw8(p, 0x55);
	if (linr8(p) != 0x55) return 0;

	linw8(p, c);
	return 1;
}
