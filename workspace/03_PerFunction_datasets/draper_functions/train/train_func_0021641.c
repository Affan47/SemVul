create_passwd_table()
{
	struct passwd *tmp;
	int count, index;

	for (count = 0; getpwent(); count++) ;

	ptable = xmalloc(sizeof(struct passwd) * (count + 1));
	memset(ptable, 0, sizeof(struct passwd) * (count + 1));
	setpwent();

	for (index = 0; (tmp = getpwent()) && index < count; index++) {
		ptable[index].pw_uid = tmp->pw_uid;
		ptable[index].pw_name = xstrdup(tmp->pw_name);
	}

	endpwent();
}
