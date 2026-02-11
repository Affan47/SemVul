IsMemberInList (uid_t user, struct group *g)
{
	gboolean result = FALSE;
	gchar *utf8_username = GetTokenName (user);

	if (!utf8_username)
		return FALSE;

	if (g) {
		gchar **users = g->gr_mem;

		while (*users) {
			gchar *u = *(users);
			if (strcmp (utf8_username, u) == 0) {
				result = TRUE;
				break;
			}
			users++;
		}
	}

	g_free (utf8_username);
	return result;
}
