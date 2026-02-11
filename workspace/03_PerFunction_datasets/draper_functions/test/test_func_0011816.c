git_transport_local(git_transport **out, void *param)
{
	transport_local *t;

	GIT_UNUSED(param);

	t = git__malloc(sizeof(transport_local));
	GITERR_CHECK_ALLOC(t);

	memset(t, 0x0, sizeof(transport_local));

	t->parent.connect = local_connect;
	t->parent.negotiate_fetch = local_negotiate_fetch;
	t->parent.download_pack = local_download_pack;
	t->parent.close = local_close;
	t->parent.free = local_free;
	t->parent.ls = local_ls;
	t->parent.is_connected = local_is_connected;
	t->parent.read_flags = local_read_flags;
	t->parent.cancel = local_cancel;

	*out = (git_transport *) t;

	return 0;
}
