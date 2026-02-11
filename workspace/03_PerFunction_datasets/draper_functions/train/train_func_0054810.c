brch(P *p)
{
	if (p->b->o.charmap->type) {
		P *q = pdup(p);
		int c = pgetc(q);
		prm(q);
		return c;
	} else {
		return brc(p);
	}
}
