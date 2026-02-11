xmalloc (size_t size) {
	void *t;

	if (size == 0)
		return NULL;

	t = malloc (size);
	if (t == NULL) {
		fprintf (stderr, _("[out of memory]"));
		exit (1);
	}

	return t;
}
