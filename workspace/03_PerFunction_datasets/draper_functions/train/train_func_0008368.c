mod_cml_patch_connection(server *srv, connection *con, plugin_data *p) {
	size_t i, j;
	plugin_config *s = p->config_storage[0];

	PATCH(ext);
#if defined(HAVE_MEMCACHE_H)
	PATCH(mc);
#endif
	PATCH(mc_namespace);
	PATCH(power_magnet);


	for (i = 1; i < srv->config_context->used; i++) {
		data_config *dc = (data_config *)srv->config_context->data[i];
		s = p->config_storage[i];


		if (!config_check_cond(srv, con, dc)) continue;


		for (j = 0; j < dc->value->used; j++) {
			data_unset *du = dc->value->data[j];

			if (buffer_is_equal_string(du->key, CONST_STR_LEN("cml.extension"))) {
				PATCH(ext);
			} else if (buffer_is_equal_string(du->key, CONST_STR_LEN("cml.memcache-hosts"))) {
#if defined(HAVE_MEMCACHE_H)
				PATCH(mc);
#endif
			} else if (buffer_is_equal_string(du->key, CONST_STR_LEN("cml.memcache-namespace"))) {
				PATCH(mc_namespace);
			} else if (buffer_is_equal_string(du->key, CONST_STR_LEN("cml.power-magnet"))) {
				PATCH(power_magnet);
			}
		}
	}

	return 0;
}
