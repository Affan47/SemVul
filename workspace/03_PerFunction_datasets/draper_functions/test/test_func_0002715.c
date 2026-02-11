pkg_key_get_role (const char *key)
{
    int i;

    if (key != NULL && *key != '\0') {
	for (i=0; pkg_lookups[i].flag > 0; i++) {
	    if (!strcmp(key, pkg_lookups[i].key)) {
		return pkg_lookups[i].flag;
	    }
	}
    }

    return UFUN_ROLE_NONE;
}
