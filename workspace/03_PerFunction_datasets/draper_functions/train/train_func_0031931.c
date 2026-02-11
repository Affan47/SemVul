c_add(COMPLEX *c1, COMPLEX *c2)
{
	COMPLEX *r;

	if (ciszero(c1))
		return clink(c2);
	if (ciszero(c2))
		return clink(c1);
	r = comalloc();
	if (!qiszero(c1->real) || !qiszero(c2->real)) {
		qfree(r->real);
		r->real = qqadd(c1->real, c2->real);
	}
	if (!qiszero(c1->imag) || !qiszero(c2->imag)) {
		qfree(r->imag);
		r->imag = qqadd(c1->imag, c2->imag);
	}
	return r;
}
