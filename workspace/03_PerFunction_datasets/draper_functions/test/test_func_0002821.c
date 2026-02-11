create_user(const char *jid, const char *name)
{
	XMPP_ROSTER_USER_REC *user;

	g_return_val_if_fail(jid != NULL, NULL);
	user = g_new(XMPP_ROSTER_USER_REC, 1);
	user->jid = g_strdup(jid);
	user->name = g_strdup(name);
	user->subscription = XMPP_SUBSCRIPTION_NONE;
	user->error = FALSE;
	user->resources = NULL;
	return user;
}
