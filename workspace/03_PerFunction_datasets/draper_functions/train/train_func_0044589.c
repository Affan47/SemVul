unitint(u, base, pbufp, width, prec)
u_long_t u;
int base;
printbuf_t *pbufp;
int width, prec;
{
	printbuf_t pbuf;
	int len, unit, uwidth, frac;

	memcpy((char *)&pbuf, (char *)pbufp, sizeof(pbuf));
	pbufp -> buf = NULL;
	pbufp -> flags |= VF_FILE;
	len = unit = uwidth = 0;
	frac = -1;
	if (pbufp -> flags & VF_STRICTWIDTH) unit++;
	if (width >= MINUNITWIDTH) for (;;) {
		if (unit) uwidth = 3;
		pbufp -> ptr = pbuf.ptr;
		len = setint(u, base, pbufp, -1, prec);
		if (len < 0) {
			len = width;
			break;
		}
		if (len + uwidth <= width) break;
		if (!(printfsizeunit[unit])) break;
		unit++;
		frac = (int)(u & (u_long_t)0x3ff);
		u >>= 10;
	}

	memcpy((char *)pbufp, (char *)&pbuf, sizeof(pbuf));
	if ((pbufp -> flags & VF_STRICTWIDTH) || len + 2 + uwidth > width)
		frac = -1;
	if (frac < 0) len = width - uwidth;
	pbufp -> flags &= ~VF_SIZEUNIT;
	pbufp -> flags |= VF_STRICTWIDTH;
	len = setint(u, base, pbufp, len, prec);
	if (len < 0) return(-1);
	if (frac >= 0) {
		width -= len + 1 + uwidth;
		u = (u_long_t)frac;
		u *= (u_long_t)1000;
		u >>= 10;
		if (setchar('.', pbufp) < 0) return(-1);
		pbufp -> flags &= (VF_NEW | VF_FILE);
		pbufp -> flags |= (VF_ZERO | VF_ASPOSSIBLE);
		if (setint(u, base, pbufp, width, prec) < 0) return(-1);
	}
	if (unit > 0) {
		if (setchar(' ', pbufp) < 0) return(-1);
		if (setchar(printfsizeunit[unit - 1], pbufp) < 0) return(-1);
		if (setchar('B', pbufp) < 0) return(-1);
	}

	return(pbufp -> ptr - pbuf.ptr);
}
