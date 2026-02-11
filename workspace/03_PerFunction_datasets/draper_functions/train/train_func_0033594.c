go_component_new_from_uri (char const *uri)
{
	char *mime_type;
	GsfInput *input;
	GOComponent *component;
	GError *err;
	size_t length;
	char *data;

	g_return_val_if_fail (uri && *uri, NULL);

	mime_type = go_get_mime_type (uri);
	if (!mime_type)
		return NULL;
	component = go_component_new_by_mime_type (mime_type);
	g_free (mime_type);
	input = go_file_open (uri, &err);
	if (err) {
		g_error_free (err);
		return NULL;
	}
	length = gsf_input_size (input);
	data = g_new (guint8, length);
	gsf_input_read (input, length, data);
	go_component_set_data (component, data, length);
	component->destroy_notify = g_free;
	return component;
}
