new_sources(int n)
{
	void *stbl;
	struct sources *src;

	src = calloc(1, sizeof(struct sources));
	if (src == NULL) {
		err_printf("new_sources: cannot alloc sources structure\n");
		return NULL;
	}
	stbl = calloc(n, sizeof(struct star));
	if (stbl == NULL) {
		err_printf("new_sources: cannot alloc star table\n");
		free(src);
		return NULL;
	}
	src->maxn = n;
	src->s = stbl;
	src->ref_count = 1;
	return src;
}
