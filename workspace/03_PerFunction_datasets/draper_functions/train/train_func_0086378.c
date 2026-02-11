asn_ulong2INTEGER(INTEGER_t *st, unsigned long value) {
	uint8_t *buf;
	uint8_t *end;
	uint8_t *b;
	int shr;

	if(value <= LONG_MAX)
		return asn_long2INTEGER(st, value);

	buf = (uint8_t *)MALLOC(1 + sizeof(value));
	if(!buf) return -1;

	end = buf + (sizeof(value) + 1);
	buf[0] = 0;
	for(b = buf + 1, shr = (sizeof(long)-1)*8; b < end; shr -= 8, b++)
		*b = (uint8_t)(value >> shr);

	if(st->buf) FREEMEM(st->buf);
	st->buf = buf;
	st->size = 1 + sizeof(value);

	return 0;
}
