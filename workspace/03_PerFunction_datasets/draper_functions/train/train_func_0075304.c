mkmaildir(const char *name)
{
	char	*np;
	size_t	sz;
	enum okay	ok = STOP;

	if (trycreate(name) == OKAY) {
		np = ac_alloc((sz = strlen(name)) + 5);
		strcpy(np, name);
		strcpy(&np[sz], "/tmp");
		if (trycreate(np) == OKAY) {
			strcpy(&np[sz], "/new");
			if (trycreate(np) == OKAY) {
				strcpy(&np[sz], "/cur");
				if (trycreate(np) == OKAY)
					ok = OKAY;
			}
		}
		ac_free(np);
	}
	return ok;
}
