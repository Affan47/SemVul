module_find(char *name)
	{
	CONF_MODULE *tmod;
	int i, nchar;
	char *p;
	p = strrchr(name, '.');

	if (p)
		nchar = p - name;
	else
		nchar = strlen(name);

	for (i = 0; i < sk_CONF_MODULE_num(supported_modules); i++)
		{
		tmod = sk_CONF_MODULE_value(supported_modules, i);
		if (!strncmp(tmod->name, name, nchar))
			return tmod;
		}

	return NULL;

	}
