uih_setmaxiter(uih_context * c, int maxiter)
{
    if (maxiter < 1)
	maxiter = 1;
    if (maxiter > 2000000)
	maxiter = 2000000;
    if (c->fcontext->maxiter != (unsigned int) maxiter) {
	c->fcontext->maxiter = maxiter;
	c->fcontext->version++;
	uih_newimage(c);
    }
}
