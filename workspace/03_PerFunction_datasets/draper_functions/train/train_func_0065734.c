add_user(XMPP_SERVER_REC *server, const char *jid, const char *name,
    const char *group_name, XMPP_ROSTER_GROUP_REC **return_group)
{
	XMPP_ROSTER_GROUP_REC *group;
	XMPP_ROSTER_USER_REC *user;

	g_return_val_if_fail(IS_XMPP_SERVER(server), NULL);
	g_return_val_if_fail(jid != NULL, NULL);
	group = find_or_add_group(server, group_name);
	user = create_user(jid, name);
	group->users = g_slist_append(group->users, user);
	if (return_group != NULL)
		*return_group = group;
	return user;
}
