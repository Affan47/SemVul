find_username_func(gconstpointer user_pointer, gconstpointer name)
{
	XMPP_ROSTER_USER_REC *user;

	g_return_val_if_fail(user_pointer != NULL, -1);
	user = (XMPP_ROSTER_USER_REC *)user_pointer;
	if (user->name == NULL)
		return -1;
	return strcmp(user->name, name);
}
