is_validfqdn(const char *f) {

    char *fqdn = strdup(f);
    if (!fqdn) return 0;
    while (fqdn[strlen(fqdn)-1] == '.')
	fqdn[strlen(fqdn)-1] = '\0';

    if (
	!(strchr(fqdn, '.'))


	|| 0 == strncasecmp(fqdn, "localhost", 9)

	|| 0 == strncmp(fqdn, "127.", 4)

	|| 0 == strcasecmp(fqdn, "linux.local")

	|| 0 == strcasecmpsuffix(fqdn, "example.org")
	|| 0 == strcasecmpsuffix(fqdn, "example.com")
	|| 0 == strcasecmpsuffix(fqdn, "example.net")
	|| 0 == strcasecmpsuffix(fqdn, ".example")
	|| 0 == strcasecmpsuffix(fqdn, ".invalid")
	|| 0 == strcasecmpsuffix(fqdn, ".local")
	|| 0 == strcasecmpsuffix(fqdn, ".localdomain")
	|| 0 == strcasecmpsuffix(fqdn, ".localhost")
	|| 0 == strcasecmpsuffix(fqdn, ".test")
	|| 0 == strcasecmpsuffix(fqdn, ".site")
	)
    {
	free(fqdn);
	return 0;
    }
    free(fqdn);
    return 1;
}
