username_find(const char **pfullname)
{
	const char *login, *fullname;

	if (find.index >= utable.cnt)
		return 0;
	login = SDSTR(utable.by_name[find.index]->login);
	if (find.len && strncmp(find.str,login,find.len))
		return 0;
	if (pfullname) {
		fullname = SDSTR(utable.by_name[find.index]->fullname);
		if (*fullname == '\0')
			fullname = login;
		*pfullname = fullname;
	}
	find.index++;
	return login;
}
