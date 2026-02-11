handle_clearlogin(sourceinfo_t *si, user_t *u)
{
	mowgli_node_t *n;

	if (authservice_loaded)
	{
		wallops("Ignoring attempt from %s to clear login name for %s",
				get_oper_name(si), u->nick);
		return;
	}

	if (u->myuser == NULL)
		return;

	slog(LG_DEBUG, "handle_clearlogin(): %s cleared login for %s (%s)",
			get_oper_name(si), u->nick, entity(u->myuser)->name);
	n = mowgli_node_find(u, &u->myuser->logins);
	if (n != NULL)
	{
		mowgli_node_delete(n, &u->myuser->logins);
		mowgli_node_free(n);
	}
	u->myuser = NULL;
}
