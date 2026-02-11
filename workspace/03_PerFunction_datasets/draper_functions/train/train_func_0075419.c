check3(const uint32_t *p, uint32_t pitch, uint32_t lines,
		  uint32_t sub_x, uint32_t sub_y,
		  uint32_t sub_w, uint32_t sub_h)
{
	uint32_t x, y;

	sub_w += sub_x;
	sub_h += sub_y;

	if (p[pitch * lines / 4 - 1] == 0x03030303) {
		fprintf(stderr, "copy failed: Not all lines have been copied back!\n");
		return -1;
	}

	for (y = 0; y < lines; ++y) {
		for (x = 0; x < pitch; x += 4, ++p) {
			uint32_t expected;
			if ((x < sub_x || x >= sub_w) ||
			    (y < sub_y || y >= sub_h))
				expected = 0x80808080;
			else
				expected = 0x04040404;
			if (*p != expected) {
				fprintf(stderr, "%u,%u should be %08x, but is %08x\n", x, y, expected, *p);
				return -1;
			}
		}
	}
	return 0;
}
