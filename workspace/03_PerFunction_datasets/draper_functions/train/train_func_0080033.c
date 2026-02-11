process_parm(const char *key, const char *value, struct param **params)
{
	const char *name, *param, *type;
	int namelen, paramlen, typelen;
	struct param *it;
	const char *colon = strchr(value, ':');
	if (colon == NULL) {
		ERR("Found invalid \"%s=%s\": missing ':'\n",
		    key, value);
		return 0;
	}

	name = value;
	namelen = colon - value;
	if (strcmp(key, "parm") == 0) {
		param = colon + 1;
		paramlen = strlen(param);
		type = NULL;
		typelen = 0;
	} else {
		param = NULL;
		paramlen = 0;
		type = colon + 1;
		typelen = strlen(type);
	}

	it = add_param(name, namelen, param, paramlen, type, typelen, params);
	if (it == NULL) {
		ERR("Out of memory!\n");
		return -ENOMEM;
	}

	return 0;
}
