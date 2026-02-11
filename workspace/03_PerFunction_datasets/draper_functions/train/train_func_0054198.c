masterconf_getstring(struct entry *e, const char *key,
				 const char *def)
{
    char k[256];
    static char v[256];
    int i;
    char *p;

    strcpy(k, key);
    strcat(k, "=");

    p = strstr(e->line, k);
    if (p) {
	p += strlen(k);
	if (*p == '"') {
	    p++;
	    for (i = 0; i < 255; i++) {
		if (*p == '"') break;
		v[i] = *p++;
	    }
	    if (*p != '"') {
		sprintf(k, "configuration file %s: missing \" on line %d",
			MASTER_CONFIG_FILENAME, e->lineno);
		fatal(k, EX_CONFIG);
	    }
	} else {

	    for (i = 0; i < 255; i++) {
		if ((!*p) || (Uisspace(*p))) break;
		v[i] = *p++;
	    }
	}
	v[i] = '\0';
	return v;
    } else {
	return def;
    }
}
