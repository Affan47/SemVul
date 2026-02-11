countor(Re *r)
{
	int n;

	n = 0;
loop:
	switch(r->type) {
	case Tor:
		n += countor(r->u.alt);
		r = r->next;
		goto loop;
	case Tclass:
		return n + r->u.x.hi - r->u.x.lo + 1;
	}
	return n;
}
