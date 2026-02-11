ved_pretend_gzip(const struct sess *sp, const uint8_t *p, ssize_t l)
{
	uint8_t buf1[5], buf2[5];
	uint16_t lx;

	lx = 65535;
	buf1[0] = 0;
	vle16enc(buf1 + 1, lx);
	vle16enc(buf1 + 3, ~lx);

	while (l > 0) {
		if (l >= 65535) {
			lx = 65535;
			(void)WRW_Write(sp->wrk, buf1, sizeof buf1);
		} else {
			lx = (uint16_t)l;
			buf2[0] = 0;
			vle16enc(buf2 + 1, lx);
			vle16enc(buf2 + 3, ~lx);
			(void)WRW_Write(sp->wrk, buf2, sizeof buf2);
		}
		(void)WRW_Write(sp->wrk, p, lx);
		sp->wrk->crc = crc32(sp->wrk->crc, p, lx);
		sp->wrk->l_crc += lx;
		l -= lx;
		p += lx;
	}

	(void)WRW_Flush(sp->wrk);
}
