zrhhdr(qdaemon, hdr)
struct sdaemon *qdaemon;
achdrval_t hdr;
{
	int c,i,type;
	unsigned long crc;

	if ((c = zgethex (qdaemon)) < 0)
		return c;
	type = c;
	crc = ICRCINIT;
	crc = UPDC32 (c, crc);

	for (i = 0; i < 4; i++) {
		if ((c = zgethex (qdaemon)) < 0)
			return c;
		crc = UPDC32 (c, crc);
		hdr[i] = (char) c;
	}
	for (i = 0; i < 4; i++) {
		if ((c = zgethex (qdaemon)) < 0)
			return c;
		crc = UPDC32 (c, crc);
	}
	if (crc != IHDRCRC)
		return ZM_ERROR;

	return type;
}
