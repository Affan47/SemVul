created_enumerator (GckUriData *uri_data,
                    const gchar *type)
{
	if (_gck_debugging) {
		gchar *attrs, *uri;
		attrs = uri_data->attributes ? gck_attributes_to_string (uri_data->attributes) : NULL;
		uri = uri_data ? gck_uri_build (uri_data, GCK_URI_FOR_TOKEN | GCK_URI_FOR_MODULE) : NULL;
		_gck_debug ("for = %s, tokens = %s, objects = %s", type, uri, attrs);
		g_free (attrs);
		g_free (uri);
	}
}
