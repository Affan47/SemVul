putbcd(d, len)
dword	d;
int	len;
{
    int		i;
    dword	n;
    byte	*p, buf[10];

    p = buf;
    while (len--) {
	*p = (int)(d % 10L);
	d /= 10;
	*p |= (int)(d % 10L) << 4;
	d /= 10;
	p++;
    }
    while (p > buf) {
	putbyte(p[-1]);
	p--;
    }
    return OK;
}
