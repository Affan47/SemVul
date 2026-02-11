user_info_hook(hook_user_req_t *req)
{
	static char buf[BUFSIZE];
	mowgli_node_t *n;
	mowgli_list_t *l;

	*buf = 0;

	l = myuser_get_membership_list(req->mu);

	MOWGLI_ITER_FOREACH(n, l->head)
	{
		groupacs_t *ga = n->data;

		if ((ga->mg->flags & MG_PUBLIC) || (req->si->smu == req->mu || has_priv(req->si, PRIV_GROUP_AUSPEX)))
		{
			if (*buf != 0)
				strlcat(buf, ", ", BUFSIZE);

			strlcat(buf, entity(ga->mg)->name, BUFSIZE);
		}
	}

	if (*buf != 0)
		command_success_nodata(req->si, _("Groups     : %s"), buf);
}
