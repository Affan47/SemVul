lookup(char *ident)
{
	struct	keystruct *p;
	int	c;


	for (p = hashtab[hash(ident) % HASHMOD]; p != NULL; p = p->next) {
		if (strequal(ident, p->text)) {
			if (compress == YES && (c = p - keyword) < ' ') {
				ident[0] = c;
			}
			return(p->text);
		}
	}

	return(NULL);
}
