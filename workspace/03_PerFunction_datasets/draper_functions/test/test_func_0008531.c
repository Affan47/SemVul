_sfpmove(reg Sfio_t * f, reg int type)
#else
static int _sfpmove(f, type)
reg Sfio_t *f;
reg int type;
#endif
{
    reg Sfpool_t *p;
    reg int n;

    if (type > 0)
	return _sfsetpool(f);
    else {
	if (!(p = f->pool))
	    return -1;
	for (n = p->n_sf - 1; n >= 0; --n)
	    if (p->sf[n] == f)
		break;
	if (n < 0)
	    return -1;

	return type == 0 ? _sfphead(p, f, n) : _sfpdelete(p, f, n);
    }
}
