at_get_pool(int *argc, char *argv[], void **arg)
{
	struct at_pool *atp = talloc(NULL, struct at_pool);
	struct at_pool_contents *p;
	void *map;
	int err;

	if (!argv[1]) {
		errno = EINVAL;
		goto fail;
	}


	if (arg == NULL)
		arg = &map;

	p = atp->p = talloc(atp, struct at_pool_contents);

	if (sscanf(argv[1], "AT:%p/%lu/%i/%i/%i/%p",
		   &p->pool, &p->poolsize, &p->fd,
		   &p->parent_rfd, &p->parent_wfd, arg) != 6) {
		errno = EINVAL;
		goto fail;
	}


	map = mmap(p->pool, p->poolsize, PROT_READ|PROT_WRITE, MAP_SHARED,
		   p->fd, 0);
	if (map != p->pool) {
		fprintf(stderr, "Mapping %lu bytes @%p gave %p\n",
			p->poolsize, p->pool, map);
		errno = ENOMEM;
		goto fail;
	}

	list_add(&pools, &p->list);
	talloc_set_destructor(p, destroy_pool);
	p->atp = atp;

	atp->ctx = talloc_add_external(atp,
				       at_realloc, talloc_lock, talloc_unlock);
	if (!atp->ctx)
		goto fail;


	err = 0;
	if (write(p->parent_wfd, &err, sizeof(err)) != sizeof(err)) {
		errno = EBADF;
		goto fail;
	}


	memmove(&argv[1], &argv[2], --(*argc));

	return atp;

fail:
	talloc_free(atp);
	return NULL;
}
