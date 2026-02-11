print_char(uint16_t ch, int count, FILE *out)
{
	char text[6];

	if (ch < 0x80) {
		text[0] = ch;
		text[1] = 0;
	} else if (ch < 0x800) {
		text[0] = 0xc0 | (ch >> 6);
		text[1] = 0x80 | (ch & 0x3f);
		text[2] = 0;
	} else {
		text[0] = 0xe0 | (ch >> 12);
		text[1] = 0x80 | ((ch >> 6) & 0x3f);
		text[2] = 0x80 | (ch & 0x3f);
		text[3] = 0;
	}

	while (count > 0) {
		fputs(text, out);
		count--;
	}
}
