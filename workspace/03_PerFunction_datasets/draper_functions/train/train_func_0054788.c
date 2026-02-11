pdup(P *p)
{
	P *n = palloc();

	n->end = 0;
	n->ptr = NULL;
	n->owner = NULL;
	enquef(P, link, p, n);
	return pset(n, p);
}
