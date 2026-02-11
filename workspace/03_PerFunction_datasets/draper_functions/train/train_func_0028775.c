module_get_root(const char *name, char **prefixes)
{
	int len;


	if (prefixes != NULL) {
		while (*prefixes != NULL) {
			len = strlen(*prefixes);
			if (strncmp(name, *prefixes, len) == 0 &&
			    name[len] == '_') {
				name += len+1;
				break;
			}
			prefixes++;
		}
	}


        len = strlen(name);
	if (len > 5 && strcmp(name+len-5, "_core") == 0)
		return g_strndup(name, len-5);

        return g_strdup(name);
}
