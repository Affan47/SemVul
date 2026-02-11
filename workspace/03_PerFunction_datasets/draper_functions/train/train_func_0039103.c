camel_content_type_unref (CamelContentType *ct)
{
	if (ct) {
		if (ct->refcount <= 1) {
			camel_header_param_list_free (ct->params);
			g_free (ct->type);
			g_free (ct->subtype);
			g_slice_free (CamelContentType, ct);
			ct = NULL;
		} else {
			ct->refcount--;
		}
	}
}
