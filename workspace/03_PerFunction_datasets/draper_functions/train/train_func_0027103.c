chirp_alloc_init(const char *rootpath, INT64_T size)
{
	struct alloc_state *a;
	time_t start, stop;
	INT64_T inuse, avail;

#ifdef CCTOOLS_OPSYS_CYGWIN
	fatal("sorry, CYGWIN cannot employ space allocation because it does not support file locking.");
#endif

	alloc_enabled = 1;
	recovery_in_progress = 1;

	debug(D_ALLOC, "### begin allocation recovery scan ###");

	if(!alloc_state_create(rootpath, size))
		fatal("couldn't create allocation in %s: %s\n", rootpath, strerror(errno));

	a = alloc_state_cache_exact(rootpath);
	if(!a)
		fatal("couldn't find allocation in %s: %s\n", rootpath, strerror(errno));


	start = time(0);
	recover(rootpath);
	size = a->size;
	inuse = a->inuse;
	avail = a->avail;
	chirp_alloc_flush();
	stop = time(0);

	debug(D_ALLOC, "### allocation recovery took %d seconds ###", stop - start);

	debug(D_ALLOC, "%sB total", string_metric(size, -1, 0));
	debug(D_ALLOC, "%sB in use", string_metric(inuse, -1, 0));
	debug(D_ALLOC, "%sB available", string_metric(avail, -1, 0));

	recovery_in_progress = 0;
}
