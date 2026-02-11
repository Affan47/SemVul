kmod_module_new(struct kmod_ctx *ctx, const char *key,
				const char *name, size_t namelen,
				const char *alias, size_t aliaslen,
				struct kmod_module **mod)
{
	struct kmod_module *m;
	size_t keylen;

	m = kmod_pool_get_module(ctx, key);
	if (m != NULL) {
		*mod = kmod_module_ref(m);
		return 0;
	}

	if (alias == NULL)
		keylen = namelen;
	else
		keylen = namelen + aliaslen + 1;

	m = malloc(sizeof(*m) + (alias == NULL ? 1 : 2) * (keylen + 1));
	if (m == NULL) {
		free(m);
		return -ENOMEM;
	}

	memset(m, 0, sizeof(*m));

	m->ctx = kmod_ref(ctx);
	m->name = (char *)m + sizeof(*m);
	memcpy(m->name, key, keylen + 1);
	if (alias == NULL) {
		m->hashkey = m->name;
		m->alias = NULL;
	} else {
		m->name[namelen] = '\0';
		m->alias = m->name + namelen + 1;
		m->hashkey = m->name + keylen + 1;
		memcpy(m->hashkey, key, keylen + 1);
	}

	m->refcount = 1;
	kmod_pool_add_module(ctx, m, m->hashkey);
	*mod = m;

	return 0;
}
