cm_store_base64_to_bin(const char *serial, int insize,
		       unsigned char *buf, int length)
{
	const char *p, *q, *chars = BASE64_ALPHABET;
	unsigned char *b;
	uint32_t u, count;

	p = serial;
	b = buf;
	u = 0;
	count = 0;
	if (insize < 0) {
		insize = strlen(serial);
	}
	for (p = serial, b = buf;
	     (((p - serial) < insize) && (*p != '\0') && (*p != '=') &&
	      ((b - buf) < length));
	     p++) {
		q = strchr(chars, *p);
		if (q != NULL) {
			switch (count % 4) {
			case 0:
				u = q - chars;
				break;
			case 1:
				u = (u << 6) | (q - chars);
				break;
			case 2:
				u = (u << 6) | (q - chars);
				break;
			case 3:
				u = (u << 6) | (q - chars);
				*b++ = (u >> 16) & 0xff;
				if (b - buf >= length) {
					break;
				}
				*b++ = (u >>  8) & 0xff;
				if (b - buf >= length) {
					break;
				}
				*b++ = (u >>  0) & 0xff;
				u = 0;
				break;
			}
			count++;
		}
	}
	switch (count % 4) {
	case 0:
	case 1:
		break;
	case 2:
		u = (u << 12);
		*b++ = (u >> 16) & 0xff;
		break;
	case 3:
		u = (u <<  6);
		*b++ = (u >> 16) & 0xff;
		if (b - buf >= length) {
			break;
		}
		*b++ = (u >>  8) & 0xff;
		break;
	}
	return b - buf;
}
