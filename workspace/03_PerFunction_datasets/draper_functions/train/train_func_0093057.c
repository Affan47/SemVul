nick_access (server * serv, char *nick, int *modechars)
{
	int i;
	unsigned int access = 0;
	char *orig = nick;

	while (*nick)
	{
		i = is_prefix_char (serv, *nick);
		if (i == -1)
			break;


		if (i != -2)
			access |= (1 << i);

		nick++;
	}

	*modechars = nick - orig;

	return access;
}
