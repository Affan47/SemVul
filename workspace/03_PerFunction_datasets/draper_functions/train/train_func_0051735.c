check_loop(struct makenode *dep, struct makenode *src)
{
	struct makelist *s;
	for (s = dep->depend; s; s = s->next) {
		if (s->node == src) {
			fprintf(stderr, "loop exists %s in %s!\n", dep->name, src->name);
			return 1;
		}
		if (loop++ > 99999) {
			fprintf(stderr, "too many loops! (loop=%d, dep->name=%s, src->name=%s)\n",
				loop, dep->name, src->name);
			return 1;
		}
		if (check_loop(s->node, src))
			return 1;
	}
	return 0;
}
