kmod_config_add_blacklist(struct kmod_config *config,
							const char *modname)
{
	char *p;
	struct kmod_list *list;

	DBG(config->ctx, "modname=%s\n", modname);

	p = strdup(modname);
	if (!p)
		goto oom_error_init;

	list = kmod_list_append(config->blacklists, p);
	if (!list)
		goto oom_error;
	config->blacklists = list;
	return 0;

oom_error:
	free(p);
oom_error_init:
	ERR(config->ctx, "out-of-memory modname=%s\n", modname);
	return -ENOMEM;
}
