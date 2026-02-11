shn_finish (shn_ctx * c, UCHAR * buf, int nbytes)
{
	int i;


	if (c->nbuf != 0) {

		macfunc (c, c->mbuf);
	}


	cycle (c);
	ADDKEY (INITKONST ^ (c->nbuf << 3));
	c->nbuf = 0;


	for (i = 0; i < N; ++i)
		c->R[i] ^= c->CRC[i];
	shn_diffuse (c);


	while (nbytes > 0) {
		cycle (c);
		if (nbytes >= 4) {
			WORD2BYTE (c->sbuf, buf);
			nbytes -= 4;
			buf += 4;
		}
		else {
			for (i = 0; i < nbytes; ++i)
				buf[i] = Byte (c->sbuf, i);
			break;
		}
	}
}
