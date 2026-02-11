del_parse(parse *p) {
	cgatsAlloc *al = p->al;
	int del_al     = p->del_al;

	if (p->b != NULL)
		al->free(al, p->b);
	if (p->tb != NULL)
		al->free(al, p->tb);
	al->free(al, p);

	if (del_al)
		al->del(al);
}
