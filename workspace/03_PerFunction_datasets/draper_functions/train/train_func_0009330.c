find_backend(const char *name)
{
	size_t i, len;
	int tentative;

	len = strlen(name);
	for (i = 0, tentative = -1; i < BACKEND_CNT; i++) {
		if (strncmp(name, backends[i]->name, len))
			continue;
		if (backends[i]->name[len] == '\0')
			return (i);
		if (tentative >= 0)
			return (-1);
		tentative = i;
	}
	return (tentative);
}
