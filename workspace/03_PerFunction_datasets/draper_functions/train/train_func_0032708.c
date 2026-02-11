pool_get_context(struct pool *p) {

	int orig = p->cur++;

	do {
		p->cur++;
		p->cur %= p->count;
		if(p->ac[p->cur] != NULL) {
			return p->ac[p->cur];
		}
	} while(p->cur != orig);

	return NULL;

}
