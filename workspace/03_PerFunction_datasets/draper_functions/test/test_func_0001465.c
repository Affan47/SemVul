filter_create_int (struct filter *chain,
				  int (*filter_func) (struct filter *),
				  void *extra)
{
	struct filter *f;


	f = (struct filter *) flex_alloc (sizeof (struct filter));
	memset (f, 0, sizeof (*f));
	f->next = NULL;
	f->argc = 0;
	f->argv = NULL;

	f->filter_func = filter_func;
	f->extra = extra;

	if (chain != NULL) {

		while (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	return f;
}
