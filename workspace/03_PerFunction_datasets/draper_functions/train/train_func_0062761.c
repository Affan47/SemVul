kmod_module_new_from_path(struct kmod_ctx *ctx,
						const char *path,
						struct kmod_module **mod)
{
	struct kmod_module *m;
	int err;
	struct stat st;
	char name[PATH_MAX];
	char *abspath;
	size_t namelen;

	if (ctx == NULL || path == NULL || mod == NULL)
		return -ENOENT;

	abspath = path_make_absolute_cwd(path);
	if (abspath == NULL) {
		DBG(ctx, "no absolute path for %s\n", path);
		return -ENOMEM;
	}

	err = stat(abspath, &st);
	if (err < 0) {
		err = -errno;
		DBG(ctx, "stat %s: %s\n", path, strerror(errno));
		free(abspath);
		return err;
	}

	if (path_to_modname(path, name, &namelen) == NULL) {
		DBG(ctx, "could not get modname from path %s\n", path);
		free(abspath);
		return -ENOENT;
	}

	m = kmod_pool_get_module(ctx, name);
	if (m != NULL) {
		if (m->path == NULL)
			m->path = abspath;
		else if (streq(m->path, abspath))
			free(abspath);
		else {
			ERR(ctx, "kmod_module '%s' already exists with different path: new-path='%s' old-path='%s'\n",
									name, abspath, m->path);
			free(abspath);
			return -EEXIST;
		}

		*mod = kmod_module_ref(m);
		return 0;
	}

	m = malloc(sizeof(*m) + namelen + 1);
	if (m == NULL)
		return -errno;

	memset(m, 0, sizeof(*m));

	m->ctx = kmod_ref(ctx);
	m->name = (char *)m + sizeof(*m);
	memcpy(m->name, name, namelen + 1);
	m->path = abspath;
	m->hashkey = m->name;
	m->refcount = 1;

	kmod_pool_add_module(ctx, m, m->hashkey);

	*mod = m;

	return 0;
}
