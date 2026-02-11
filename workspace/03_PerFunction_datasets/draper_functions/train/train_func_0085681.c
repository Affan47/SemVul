g_mime_content_type_set_params (GMimeContentType *mime_type, GMimeParam *params)
{
	g_return_if_fail (GMIME_IS_CONTENT_TYPE (mime_type));


	g_hash_table_remove_all (mime_type->param_hash);
	g_mime_param_destroy (mime_type->params);
	mime_type->params = params;

	while (params != NULL) {
		g_hash_table_insert (mime_type->param_hash, params->name, params);
		params = params->next;
	}

	g_mime_event_emit (mime_type->priv, NULL);
}
