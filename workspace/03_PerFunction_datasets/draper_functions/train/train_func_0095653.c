mode_set(IRC_SERVER_REC *server, GString *str,
		     char type, char mode, int user)
{
	g_return_if_fail(str != NULL);

	if (type == '-')
		mode_remove(server, str, mode, user);
        else
		mode_add_sorted(server, str, mode, NULL, user);
}
