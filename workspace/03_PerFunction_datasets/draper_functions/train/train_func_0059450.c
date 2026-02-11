str_code_hqw(_WString* s, uint8_t src[8])
{
	int8_t* buf;
	int i = 0, shift = 0;
	uint32_t x = RULONG(&src[sizeof(int32_t)]);
	int t;

	buf = &s->p[s->pos];
	buf[0] = '0';
	buf[1] = 'x';
	buf += 2;

	for (shift = 28; shift != -4; shift -= 4) {
		t = (x >> shift) & 0xf;
		if (i | t) buf[i++] = NIBBLE_TO_CHR;
	}

	x = RULONG(src);
	for (shift = 28; shift != 0; shift -= 4) {
		t = (x >> shift) & 0xf;
		if (i | t) buf[i++] = NIBBLE_TO_CHR;
	}
	t = x & 0xf;
	buf[i++] = NIBBLE_TO_CHR;

	s->pos += i + 2;
	buf[i] = '\0';
}
