parseVariable(const char *sql, int *eaten)
{
	int			i = 0;
	char	   *name;

	do
	{
		i++;
	} while (isalnum((unsigned char) sql[i]) || sql[i] == '_');
	if (i == 1)
		return NULL;

	name = pg_malloc(i);
	memcpy(name, &sql[1], i - 1);
	name[i - 1] = '\0';

	*eaten = i;
	return name;
}
