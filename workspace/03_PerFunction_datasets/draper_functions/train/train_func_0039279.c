set_chan_app_data(struct ast_channel *chan, const char *src_app_data)
{
	struct ast_datastore *datastore;
	char *dst_app_data;

	datastore = ast_datastore_alloc(&channel_app_data_datastore, NULL);
	if (!datastore) {
		return -1;
	}

	dst_app_data = ast_malloc(strlen(src_app_data) + 1);
	if (!dst_app_data) {
		ast_datastore_free(datastore);
		return -1;
	}

	ast_channel_data_set(chan, strcpy(dst_app_data, src_app_data));
	datastore->data = dst_app_data;
	ast_channel_datastore_add(chan, datastore);
	return 0;
}
