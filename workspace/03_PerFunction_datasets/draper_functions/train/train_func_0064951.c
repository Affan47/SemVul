make_remote(const char *name, int len)
{
	int i, empty = -1;

	for (i = 0; i < allocated_remotes; i++) {
		if (!remotes[i]) {
			if (empty < 0)
				empty = i;
		} else {
			if (len ? (!strncmp(name, remotes[i]->name, len) &&
				   !remotes[i]->name[len]) :
			    !strcmp(name, remotes[i]->name))
				return remotes[i];
		}
	}

	if (empty < 0) {
		empty = allocated_remotes;
		allocated_remotes += allocated_remotes ? allocated_remotes : 1;
		remotes = xrealloc(remotes,
				   sizeof(*remotes) * allocated_remotes);
		memset(remotes + empty, 0,
		       (allocated_remotes - empty) * sizeof(*remotes));
	}
	remotes[empty] = xcalloc(1, sizeof(struct remote));
	if (len)
		remotes[empty]->name = xstrndup(name, len);
	else
		remotes[empty]->name = xstrdup(name);
	return remotes[empty];
}
