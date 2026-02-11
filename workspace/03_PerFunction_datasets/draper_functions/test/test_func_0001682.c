init_mr97310a_decoder(void)
{
	int i;
	int is_abs, val, len;

	for (i = 0; i < 256; ++i) {
		is_abs = 0;
		val = 0;
		len = 0;
		if ((i & 0x80) == 0) {

			val = 0;
			len = 1;
		} else if ((i & 0xe0) == 0xc0) {

			val = -3;
			len = 3;
		} else if ((i & 0xe0) == 0xa0) {

			val = 3;
			len = 3;
		} else if ((i & 0xf0) == 0x80) {

			val = 8;
			len = 4;
		} else if ((i & 0xf0) == 0x90) {

			val = -8;
			len = 4;
		} else if ((i & 0xf0) == 0xf0) {

			val = -20;
			len = 4;
		} else if ((i & 0xf8) == 0xe0) {

			val = 20;
			len = 5;
		} else if ((i & 0xf8) == 0xe8) {

			is_abs = 1;
			val = 0;
			len = 5;
		}
		table[i].is_abs = is_abs;
		table[i].val = val;
		table[i].len = len;
	}
	decoder_initialized = 1;
}
