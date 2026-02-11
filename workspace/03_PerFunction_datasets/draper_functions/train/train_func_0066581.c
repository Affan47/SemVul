ncr_buf(inbytes)
	u_int		inbytes;
{
	u_int		i;
	int		c;
	reg u_char     *inptr, *pakptr;
	static int	cnt;

	inptr = pinbuf;
	pakptr = pakbuf;

	if (state == NOHIST) {
		lastc = (-1);
		cnt = 1;
		state = SENTCHAR;
	}
	for (i = 0; i < inbytes; i++) {
		c = *inptr++;
		if (c == lastc && cnt < 255)
			cnt++;
		else {
			if (cnt == 2) {
				*pakptr++ = lastc;
			} else if (cnt > 2) {
				*pakptr++ = DLE;
				*pakptr++ = cnt;
			}
			*pakptr++ = c;
			lastc = c;
			cnt = 1;
		}
		if (c == DLE) {
			*pakptr++ = '\0';
			lastc = (-1);
		}
	}
	if (inbytes < MYBUF && cnt > 1) {
		if (cnt == 2)
			*pakptr++ = lastc;
		else {
			*pakptr++ = DLE;
			*pakptr++ = cnt;
		}
	}
	return (pakptr - pakbuf);
}
