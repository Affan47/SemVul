camel_url_copy (CamelURL *in)
{
	CamelURL *out;

	g_return_val_if_fail (in != NULL, NULL);

	out = g_malloc0 (sizeof (*out));
	out->protocol = g_strdup (in->protocol);
	out->user = g_strdup (in->user);
	out->authmech = g_strdup (in->authmech);
	out->host = g_strdup (in->host);
	out->port = in->port;
	out->path = g_strdup (in->path);
	out->params = NULL;
	if (in->params)
		g_datalist_foreach (&((CamelURL *) in)->params, copy_param, &out->params);
	out->query = g_strdup (in->query);
	out->fragment = g_strdup (in->fragment);

	return out;
}
