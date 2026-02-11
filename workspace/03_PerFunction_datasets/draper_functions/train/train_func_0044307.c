iks_id_cmp (iksid *a, iksid *b, int parts)
{
	int diff;

	if (!a || !b) return (IKS_ID_RESOURCE | IKS_ID_USER | IKS_ID_SERVER);
	diff = 0;
	if (parts & IKS_ID_RESOURCE && !(!a->resource && !b->resource) && iks_strcmp (a->resource, b->resource) != 0)
		diff += IKS_ID_RESOURCE;
	if (parts & IKS_ID_USER && !(!a->user && !b->user) && iks_strcasecmp (a->user, b->user) != 0)
		diff += IKS_ID_USER;
	if (parts & IKS_ID_SERVER && !(!a->server && !b->server) && iks_strcmp (a->server, b->server) != 0)
		diff += IKS_ID_SERVER;
	return diff;
}
