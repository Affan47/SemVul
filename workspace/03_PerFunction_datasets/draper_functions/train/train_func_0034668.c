data_provider_print_cli(int fd, const char *name,
	struct ao2_container *container, struct ast_str *path)
{
	struct ao2_iterator i;
	struct ast_str *current_path;
	struct data_provider *provider;

	current_path = ast_str_create(60);
	if (!current_path) {
		return;
	}

	ast_str_reset(current_path);
	if (path) {
		ast_str_set(&current_path, 0, "%s/%s", ast_str_buffer(path), name);
	} else {
		ast_str_set(&current_path, 0, "%s", name);
	}

	i = ao2_iterator_init(container, 0);
	while ((provider = ao2_iterator_next(&i))) {
		if (provider->handler) {

			ast_cli(fd, "%s/%s (", ast_str_buffer(current_path),
				provider->name);
			if (provider->handler->get) {
				ast_cli(fd, "get");
			}
			ast_cli(fd, ") [%s]\n", provider->registrar);
		}
		data_provider_print_cli(fd, provider->name, provider->children,
			current_path);
		ao2_ref(provider, -1);
	}
	ao2_iterator_destroy(&i);

	ast_free(current_path);
}
