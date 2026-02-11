insmod_do_module(struct kmod_module *mod, const char *extra_opts,
				bool do_dependencies, struct array *recursion)
{
	const char *modname = kmod_module_get_name(mod);
	const char *conf_opts = kmod_module_get_options(mod);
	struct kmod_list *pre = NULL, *post = NULL;
	const char *cmd = NULL;
	char *opts = NULL;
	int err;

	if (!ignore_commands) {
		err = kmod_module_get_softdeps(mod, &pre, &post);
		if (err < 0) {
			WRN("could not get softdeps of '%s': %s\n",
						modname, strerror(-err));
			return err;
		}

		cmd = kmod_module_get_install_commands(mod);
	}

	if (cmd == NULL && !ignore_loaded) {
		int state = kmod_module_get_initstate(mod);

		if (state == KMOD_MODULE_BUILTIN) {
			if (first_time) {
				err = -EEXIST;
				LOG("Module %s already in kernel (builtin).\n",
								modname);
			} else
				err = 0;

			goto error;
		} else if (state == KMOD_MODULE_LIVE) {
			if (first_time) {
				err = -EEXIST;
				LOG("Module %s already in kernel.\n", modname);

			} else
				err = 0;

			goto error;
		}
	}

	if (cmd == NULL && kmod_module_get_path(mod) == NULL) {
		err = -ENOENT;
		LOG("Module %s not found.\n", modname);
		goto error;
	}

	err = insmod_do_deps_list(pre, false, recursion);
	if (err == -ELOOP)
		goto error;

	if (do_dependencies) {
		struct kmod_list *deps = kmod_module_get_dependencies(mod);

		err = insmod_do_deps_list(deps, true, recursion);
		if (err < 0)
			goto error;
	}

	if ((err = concat_options(conf_opts, extra_opts, &opts)) < 0)
		goto error;

	if (cmd == NULL)
		err = insmod_do_insert_module(mod, opts);
	else
		err = command_do(mod, "install", cmd, NULL);

	if (err < 0)
		goto error;

	err = insmod_do_deps_list(post, false, recursion);

error:
	kmod_module_unref_list(pre);
	kmod_module_unref_list(post);
	free(opts);

	return err;
}
