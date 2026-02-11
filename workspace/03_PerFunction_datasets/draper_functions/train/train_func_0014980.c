write_u(char *p, char *ebuf, const knh_ldata2_t *d)
{
	if(ebuf - p < 32) return NULL;
	kuintptr_t u = d->uvalue / 10, r = d->uvalue % 10;
	if(u != 0) {
		p = write_d(p, ebuf, u);
	}
	p[0] = ('0' + r);
	return p + 1;
}
