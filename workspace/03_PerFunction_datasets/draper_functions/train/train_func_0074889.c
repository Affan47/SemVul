auth_newstate(identifier, cacheid)
const char *identifier;
const char *cacheid;
{
    struct auth_state *newstate;
    struct passwd *pwd;
    struct group *grp;
    char **mem;

    identifier = auth_canonifyid(identifier);
    if (!identifier) return 0;
    if (!strncmp(identifier, "group:", 6)) return 0;

    pwd = getpwnam(identifier);

    newstate = (struct auth_state *)xmalloc(sizeof(struct auth_state));

    strcpy(newstate->userid, identifier);
    newstate->ngroups = 0;
    newstate->group = (char **) 0;

    setgrent();
    while (grp = getgrent()) {
	for (mem = grp->gr_mem; *mem; mem++) {
	    if (!strcmp(*mem, identifier)) break;
	}

	if (*mem || (pwd && pwd->pw_gid == grp->gr_gid)) {
	    newstate->ngroups++;
	    newstate->group = (char **)xrealloc((char *)newstate->group,
						newstate->ngroups * sizeof(char *));
	    newstate->group[newstate->ngroups-1] = xstrdup(grp->gr_name);
	}
    }
    endgrent();
    return newstate;
}
