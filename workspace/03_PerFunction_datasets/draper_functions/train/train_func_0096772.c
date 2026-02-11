__absname(env, pref, name, newnamep)
	ENV *env;
	char *pref, *name, **newnamep;
{
	size_t l_pref, l_name;
	int isabspath, ret;
	char *newname;

	l_name = strlen(name);
	isabspath = __os_abspath(name);
	l_pref = isabspath ? 0 : strlen(pref);


	if ((ret = __os_malloc(env,
	    l_pref + l_name + 2, &newname)) != 0)
		return (ret);
	*newnamep = newname;


	if (!isabspath) {
		memcpy(newname, pref, l_pref);
		if (strchr(PATH_SEPARATOR, newname[l_pref - 1]) == NULL)
			newname[l_pref++] = PATH_SEPARATOR[0];
	}
	memcpy(newname + l_pref, name, l_name + 1);

	return (0);
}
