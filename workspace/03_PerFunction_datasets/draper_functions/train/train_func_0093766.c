braille_write(u16 *buf)
{
	static u16 lastwrite[WIDTH];
	unsigned char data[1 + 1 + 2*WIDTH + 2 + 1], csum = 0, *c;
	u16 out;
	int i;

	if (!braille_co)
		return;

	if (!memcmp(lastwrite, buf, WIDTH * sizeof(*buf)))
		return;
	memcpy(lastwrite, buf, WIDTH * sizeof(*buf));

#define SOH 1
#define STX 2
#define ETX 2
#define EOT 4
#define ENQ 5
	data[0] = STX;
	data[1] = '>';
	csum ^= '>';
	c = &data[2];
	for (i = 0; i < WIDTH; i++) {
		out = buf[i];
		if (out >= 0x100)
			out = '?';
		else if (out == 0x00)
			out = ' ';
		csum ^= out;
		if (out <= 0x05) {
			*c++ = SOH;
			out |= 0x40;
		}
		*c++ = out;
	}

	if (csum <= 0x05) {
		*c++ = SOH;
		csum |= 0x40;
	}
	*c++ = csum;
	*c++ = ETX;

	braille_co->write(braille_co, data, c - data);
}
