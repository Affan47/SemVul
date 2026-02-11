rtnl_tab_initialize(const char *file, char **tab, int size)
{
	char buf[512];
	FILE *fp;

	fp = fopen(file, "r");
	if (!fp)
		return;
	while (fgets(buf, sizeof(buf), fp)) {
		char *p = buf;
		int id;
		char namebuf[512];

		while (*p == ' ' || *p == '\t')
			p++;
		if (*p == '#' || *p == '\n' || *p == 0)
			continue;
		if (sscanf(p, "0x%x %s\n", &id, namebuf) != 2 &&
		    sscanf(p, "0x%x %s #", &id, namebuf) != 2 &&
		    sscanf(p, "%d %s\n", &id, namebuf) != 2 &&
		    sscanf(p, "%d %s #", &id, namebuf) != 2) {
			fprintf(stderr, "Database %s is corrupted at %s\n",
				file, p);
			fclose(fp);
			return;
		}

		if (id<0 || id>size)
			continue;

		tab[id] = strdup(namebuf);
	}
	fclose(fp);
}
