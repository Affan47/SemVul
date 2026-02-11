git_transport_local(git_transport **out)
{
	transport_local *t;

	t = git__malloc(sizeof(transport_local));
	GITERR_CHECK_ALLOC(t);

	memset(t, 0x0, sizeof(transport_local));

	t->parent.connect = local_connect;
	t->parent.ls = local_ls;
	t->parent.negotiate_fetch = local_negotiate_fetch;
	t->parent.close = local_close;
	t->parent.free = local_free;

	*out = (git_transport *) t;

	return 0;
}
