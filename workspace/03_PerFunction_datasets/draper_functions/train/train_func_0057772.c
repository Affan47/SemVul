pfill(P *p, long to, int usetabs)
{
	if (usetabs=='\t')
		while (piscol(p) < to)
			if (p->col + p->b->o.tab - p->col % p->b->o.tab <= to) {
				binsc(p, '\t');
				pgetc(p);
			} else {
				binsc(p, ' ');
				pgetc(p);
			}
	else
		while (piscol(p) < to) {
			binsc(p, usetabs);
			pgetc(p);
		}
}
