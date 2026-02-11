expand_name(char *base, char *name, char **portstr)
{
	char *s;

	if (!base)
		return 0;

	if (!strchr(base, '@')) {
		if (netprefix[0] != 0 && !strchr(base, '#'))
			snprintf(name, NODEIDLEN, "%s#%s", netprefix, base);
		else
			strncpy(name, base, NODEIDLEN - 1);
		if (portstr)
			*portstr = NULL;
		PDEBUG("name %s port %s", name, portstr ? *portstr : 0);
		return name;
	}

	snprintf(name, NODEIDLEN, "%s%s", base[0] == '@' ? netprefix : "", base);
	PDEBUG("alias %s", name);

	if (!(s = map_alias(name)))
		return 0;

	strncpy(name, s, NODEIDLEN - 1);

	if (portstr) {
		*portstr = name;
		strsep(portstr, "[");
	}
	PDEBUG("name %s port %s", name, portstr ? *portstr : 0);
	return name;
}
