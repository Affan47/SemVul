OBJECT_IDENTIFIER_get_single_arc(uint8_t *arcbuf, unsigned int arclen, signed int add, void *rvbufp, unsigned int rvsize) {
	unsigned LE GCC_NOTUSED = 1;
	uint8_t *arcend = arcbuf + arclen;
	unsigned int cache = 0;
	unsigned char *rvbuf = (unsigned char *)rvbufp;
	unsigned char *rvstart = rvbuf;
	int inc;

	rvsize *= CHAR_BIT;
	arclen *= 7;


	if(arclen > rvsize) {
		if(arclen > (rvsize + CHAR_BIT)) {
			errno = ERANGE;
			return -1;
		} else {


			uint8_t mask = (0xff << (7-(arclen - rvsize))) & 0x7f;
			if((*arcbuf & mask)) {
				errno = ERANGE;
				return -1;
			}

			arclen -= 7;
			cache = *arcbuf & 0x7f;
			arcbuf++;
		}
	}


	if(rvsize == (CHAR_BIT * sizeof(unsigned long))) {
		unsigned long accum;

		for(accum = cache; arcbuf < arcend; arcbuf++)
			accum = (accum << 7) | (*arcbuf & ~0x80);
		if(accum < (unsigned)-add) {
			errno = ERANGE;
			return -1;
		}
		*(unsigned long *)rvbuf = accum + add;
		return 0;
	}

#ifndef	WORDS_BIGENDIAN
	if(*(unsigned char *)&LE) {

		rvbuf += rvsize / CHAR_BIT - 1;
		rvstart--;
		inc = -1;
	} else
#endif
		inc = +1;

	{
		int bits;


		for(bits = rvsize - arclen;
			bits > CHAR_BIT;
				rvbuf += inc, bits -= CHAR_BIT)
				*rvbuf = 0;


		for(; arcbuf < arcend; arcbuf++) {
			cache = (cache << 7) | (*arcbuf & 0x7f);
			bits += 7;
			if(bits >= CHAR_BIT) {
				bits -= CHAR_BIT;
				*rvbuf = (cache >> bits);
				rvbuf += inc;
			}
		}
		if(bits) {
			*rvbuf = cache;
			rvbuf += inc;
		}
	}

	if(add) {
		for(rvbuf -= inc; rvbuf != rvstart; rvbuf -= inc) {
			int v = add + *rvbuf;
			if(v & (-1 << CHAR_BIT)) {
				*rvbuf = (unsigned char)(v + (1 << CHAR_BIT));
				add = -1;
			} else {
				*rvbuf = v;
				break;
			}
		}
		if(rvbuf == rvstart) {

			errno = ERANGE;
			return -1;
		}
	}

	return 0;
}
