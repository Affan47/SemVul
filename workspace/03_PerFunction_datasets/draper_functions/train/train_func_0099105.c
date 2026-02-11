custom_log(struct ast_cdr *cdr)
{
	struct ast_channel *dummy;
	struct ast_str *str;
	struct cdr_config *config;


	if (!(str = ast_str_thread_get(&custom_buf, 16))) {
		return -1;
	}

	dummy = ast_dummy_channel_alloc();
	if (!dummy) {
		ast_log(LOG_ERROR, "Unable to allocate channel for variable subsitution.\n");
		return -1;
	}


	ast_channel_cdr_set(dummy, ast_cdr_dup(cdr));

	AST_RWLIST_RDLOCK(&sinks);

	AST_LIST_TRAVERSE(&sinks, config, list) {
		FILE *out;

		ast_str_substitute_variables(&str, 0, dummy, config->format);


		ast_mutex_lock(&config->lock);


		if ((out = fopen(config->filename, "a"))) {
			fputs(ast_str_buffer(str), out);
			fflush(out);
			fclose(out);
		} else {
			ast_log(LOG_ERROR, "Unable to re-open master file %s : %s\n", config->filename, strerror(errno));
		}

		ast_mutex_unlock(&config->lock);
	}

	AST_RWLIST_UNLOCK(&sinks);

	ast_channel_unref(dummy);

	return 0;
}
