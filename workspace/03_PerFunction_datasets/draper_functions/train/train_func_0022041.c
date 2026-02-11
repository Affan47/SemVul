_sfpdelete(Sfpool_t * p, Sfio_t * f, int n)
#else
static int _sfpdelete(p, f, n)
Sfpool_t *p;
Sfio_t *f;
int n;
#endif
{
    POOLMTXSTART(p);

    p->n_sf -= 1;
    for (; n < p->n_sf; ++n)
	p->sf[n] = p->sf[n + 1];

    f->pool = NIL(Sfpool_t *);
    f->mode &= ~SF_POOL;

    if (p->n_sf == 0 || p == &_Sfpool) {
	if (p != &_Sfpool)
	    delpool(p);
	goto done;
    }


    for (n = 0; n < p->n_sf; ++n)
	if (!SFFROZEN(p->sf[n]))
	    break;
    if (n < p->n_sf && n > 0) {
	f = p->sf[n];
	p->sf[n] = p->sf[0];
	p->sf[0] = f;
    }


    f = p->sf[0];
    f->mode &= ~SF_POOL;
    if (!SFFROZEN(f))
	_SFOPEN(f);


    if (p->n_sf == 1) {
	_sfpdelete(p, f, 0);
	_sfsetpool(f);
    }

  done:
    POOLMTXRETURN(p, 0);
}
