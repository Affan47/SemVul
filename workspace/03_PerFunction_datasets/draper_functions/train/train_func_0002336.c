hashlist_init(hashlist_t *l, unsigned int nodes, unsigned int length) {

	l->entries = 0;
	l->length = length + 1;

	if (nodes != 0) {
		l->size = nodes;
		l->hashbuf = malloc(l->size * l->length);
		if (l->hashbuf == NULL)
			l->size = 0;
	} else {
		l->size = 0;
		l->hashbuf = NULL;
	}
}
