purge_comments(char *comments)
{
	char *c = comments;
	int overwrite = 0;
	char ch;


	while ((ch = *c)) {
		if (ch == '#')
			overwrite = 1;
		if (ch == '\n')
			overwrite = 0;
		if (overwrite)
			*c = ' ';

		c++;
	}

	return comments;
}
