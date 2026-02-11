stats_set_uri(struct uri_auth **root, char *uri)
{
	struct uri_auth *u;
	char *uri_copy;
	int uri_len;

	uri_len  = strlen(uri);
	if ((uri_copy = strdup(uri)) == NULL)
		goto out_uri;

	if ((u = stats_check_init_uri_auth(root)) == NULL)
		goto out_u;

	free(u->uri_prefix);
	u->uri_prefix = uri_copy;
	u->uri_len = uri_len;
	return u;

 out_u:
	free(uri_copy);
 out_uri:
	return NULL;
}
