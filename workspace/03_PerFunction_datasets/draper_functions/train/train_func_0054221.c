list_load_from_data (GSList ** list, char *ibuf, int size)
{
	char cmd[384];
	char name[128];
	char *buf;
	int pnt = 0;

	cmd[0] = 0;
	name[0] = 0;

	while (buf_get_line (ibuf, &buf, &pnt, size))
	{
		if (*buf != '#')
		{
			if (!g_ascii_strncasecmp (buf, "NAME ", 5))
			{
				safe_strcpy (name, buf + 5, sizeof (name));
			}
			else if (!g_ascii_strncasecmp (buf, "CMD ", 4))
			{
				safe_strcpy (cmd, buf + 4, sizeof (cmd));
				if (*name)
				{
					list_addentry (list, cmd, name);
					cmd[0] = 0;
					name[0] = 0;
				}
			}
		}
	}
}
