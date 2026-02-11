shn_stream (shn_ctx * c, UCHAR * buf, int nbytes)
{
	UCHAR *endbuf;


	while (c->nbuf != 0 && nbytes != 0) {
		*buf++ ^= c->sbuf & 0xFF;
		c->sbuf >>= 8;
		c->nbuf -= 8;
		--nbytes;
	}


	endbuf = &buf[nbytes & ~((WORD) 0x03)];
	while (buf < endbuf) {
		cycle (c);
		XORWORD (c->sbuf, buf);
		buf += 4;
	}


	nbytes &= 0x03;
	if (nbytes != 0) {
		cycle (c);
		c->nbuf = 32;
		while (c->nbuf != 0 && nbytes != 0) {
			*buf++ ^= c->sbuf & 0xFF;
			c->sbuf >>= 8;
			c->nbuf -= 8;
			--nbytes;
		}
	}
}
