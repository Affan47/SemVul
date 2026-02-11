get_client_block_buffer (request_rec *r, uint32_t requested_size, uint32_t *actual_size)
{
	request_data *rd = ap_get_module_config (r->request_config, &mono_module);

	if (rd == NULL)	{
		rd = apr_pcalloc (r->pool, sizeof (request_data));
		ap_set_module_config (r->request_config, &mono_module, rd);
	}

	if (requested_size > 1024 * 1024)
		requested_size = 1024 * 1024;

	if (requested_size > rd->client_block_buffer_size) {
		rd->client_block_buffer = apr_pcalloc (r->pool, requested_size);
		rd->client_block_buffer_size = requested_size;
	}

	*actual_size = requested_size;
	return rd->client_block_buffer;
}
