str2role(str)
	char *str;
{
	int i, len;


	if (!str || !str[0])
	    return ROLE_NONE;


	len = strlen(str);
	for (i = 0; roles[i].name.m; i++) {

	    if (!strncmpi(str, roles[i].name.m, len))
		return i;

	    if (roles[i].name.f && !strncmpi(str, roles[i].name.f, len))
		return i;

	    if (!strcmpi(str, roles[i].filecode))
		return i;
	}

	if ((len == 1 && (*str == '*' || *str == '@')) ||
		!strncmpi(str, randomstr, len))
	    return ROLE_RANDOM;


	return ROLE_NONE;
}
