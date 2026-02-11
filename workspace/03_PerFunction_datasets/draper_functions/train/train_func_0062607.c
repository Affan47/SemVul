add_checker (char * name)
{
	char libname[LIB_CHECKER_NAMELEN];
	void * handle;
	struct checker * c;
	char *errstr;

	c = alloc_checker();
	if (!c)
		return NULL;
	snprintf(libname, LIB_CHECKER_NAMELEN, "%s/libcheck%s.so",
		 conf->multipath_dir, name);
	condlog(3, "loading %s checker", libname);
	handle = dlopen(libname, RTLD_NOW);
	errstr = dlerror();
	if (errstr != NULL)
	condlog(0, "A dynamic linking error occurred: (%s)", errstr);
	if (!handle)
		goto out;

	c->check = (int (*)(struct checker *)) dlsym(handle, "libcheck_check");
	errstr = dlerror();
	if (errstr != NULL)
	condlog(0, "A dynamic linking error occurred: (%s)", errstr);
	if (!c->check)
		goto out;

	c->init = (int (*)(struct checker *)) dlsym(handle, "libcheck_init");
	errstr = dlerror();
	if (errstr != NULL)
	condlog(0, "A dynamic linking error occurred: (%s)", errstr);
	if (!c->init)
		goto out;

	c->free = (void (*)(struct checker *)) dlsym(handle, "libcheck_free");
	errstr = dlerror();
	if (errstr != NULL)
	condlog(0, "A dynamic linking error occurred: (%s)", errstr);
	if (!c->free)
		goto out;

	snprintf(c->name, CHECKER_NAME_LEN, "%s", name);
	c->fd = 0;
	c->sync = 1;
	list_add(&c->node, &checkers);
	return c;
out:
	free_checker(c);
	return NULL;
}
