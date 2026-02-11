Unicode_String_to_UTF8_String(uint8_t * s, const uint16_t * pwcs, int maxlen)
{
	const uint16_t *ip;
	uint8_t *op;
	int size;

	op = s;
	ip = pwcs;
	while (*ip && maxlen > 0) {
		if (*ip > 0x7f) {
			size = Unicode_Character_to_UTF8_Character(op, *ip, maxlen);
			if (size == -1) {

				maxlen--;
			} else {
				op += size;
				maxlen -= size;
			}
		} else {
			*op++ = (uint8_t) * ip;
			maxlen--;
		}
		ip++;
	}
	return (op - s);
}
