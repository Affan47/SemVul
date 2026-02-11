sechk_lib_module_clear_option(sechk_module_t * module, char *option)
{
	apol_vector_t *new_opts = NULL;
	sechk_name_value_t *needle = NULL, *nv = NULL, *tmp = NULL;
	int error = 0;
	size_t i = 0;

	if (!module || !option) {
		errno = EINVAL;
		return -1;
	}

	if (!(needle = sechk_name_value_new(option, NULL))) {
		error = errno;
		ERR(module->parent_lib->policy, "Clearing option %s: %s.", option, strerror(error));
		errno = error;
		return -1;
	}


	if (apol_vector_get_index(module->options, needle, sechk_option_name_compare, NULL, &i) < 0) {
		sechk_name_value_free(needle);
		return 0;
	}

	if (!(new_opts = apol_vector_create(sechk_name_value_free))) {
		error = errno;
		ERR(module->parent_lib->policy, "%s", strerror(error));
		errno = error;
		return -1;
	}


	for (i = 0; i < apol_vector_get_size(module->options); i++) {
		nv = apol_vector_get_element(module->options, i);
		if (strcmp(nv->name, needle->name)) {
			if (!(tmp = sechk_name_value_new(nv->name, nv->value))) {
				error = errno;
				WARN(module->parent_lib->policy, "Clearing option %s: %s.", option, strerror(error));
				goto err;
			}
			if (apol_vector_append(new_opts, (void *)tmp)) {
				error = errno;
				WARN(module->parent_lib->policy, "Clearing option %s: %s.", option, strerror(error));
				goto err;
			}
			tmp = NULL;
		}
	}

	sechk_name_value_free(needle);
	apol_vector_destroy(&module->options);
	module->options = new_opts;

	return 0;

      err:
	sechk_name_value_free(tmp);
	sechk_name_value_free(needle);
	apol_vector_destroy(&new_opts);
	errno = error;
	return -1;
}
