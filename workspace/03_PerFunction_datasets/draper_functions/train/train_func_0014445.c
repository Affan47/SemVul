findspan(const u_char** bpp, int bs, int be, const u_char* tab)
{
    const u_char *bp = *bpp;
    int bits = be - bs;
    int n, span;


    if (bits > 0 && (n = (bs & 7))) {
	span = tab[(*bp << n) & 0xff];
	if (span > 8-n)
	    span = 8-n;
	if (span > bits)
	    span = bits;
	if (n+span < 8)
	    goto done;
	bits -= span;
	bp++;
    } else
	span = 0;


    while (bits >= 8) {
	n = tab[*bp];
	span += n;
	bits -= n;
	if (n < 8)
	    goto done;
	bp++;
    }


    if (bits > 0) {
	n = tab[*bp];
	span += (n > bits ? bits : n);
    }
done:
    *bpp = bp;
    return (span);
}
