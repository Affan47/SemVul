ast_channel_cc_params_init(struct ast_channel *chan,
		const struct ast_cc_config_params *base_params)
{
	struct ast_cc_config_params *cc_params;
	struct ast_datastore *cc_datastore;

	if (!(cc_params = ast_cc_config_params_init())) {
		return -1;
	}

	if (!(cc_datastore = ast_datastore_alloc(&cc_channel_datastore_info, NULL))) {
		ast_cc_config_params_destroy(cc_params);
		return -1;
	}

	if (base_params) {
		ast_cc_copy_config_params(cc_params, base_params);
	}
	cc_datastore->data = cc_params;
	ast_channel_datastore_add(chan, cc_datastore);
	return 0;
}
