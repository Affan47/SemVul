add_prio (char * name)
{
	char libname[LIB_PRIO_NAMELEN];
	void * handle;
	struct prio * p;
	char *errstr;

	p = alloc_prio();
	if (!p)
		return NULL;
	snprintf(libname, LIB_PRIO_NAMELEN, "%s/libprio%s.so",
		 conf->multipath_dir, name);
	condlog(3, "loading %s prioritizer", libname);
	handle = dlopen(libname, RTLD_NOW);
	errstr = dlerror();
	if (errstr != NULL)
	condlog(0, "A dynamic linking error occurred: (%s)", errstr);
	if (!handle)
		goto out;
	p->getprio = (int (*)(struct path *, char *)) dlsym(handle, "getprio");
	errstr = dlerror();
	if (errstr != NULL)
	condlog(0, "A dynamic linking error occurred: (%s)", errstr);
	if (!p->getprio)
		goto out;
	snprintf(p->name, PRIO_NAME_LEN, "%s", name);
	list_add(&p->node, &prioritizers);
	return p;
out:
	free_prio(p);
	return NULL;
}
