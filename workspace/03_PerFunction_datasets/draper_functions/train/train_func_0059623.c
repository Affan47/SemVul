alloc_searchdn(const char *value)
{
	struct ldap_searchdn *sdn;
	char *val;

	sdn = malloc(sizeof(struct ldap_searchdn));
	if (!sdn)
		return NULL;

	val = strdup(value);
	if (!val) {
		free(sdn);
		return NULL;
	}

	sdn->basedn = val;
	sdn->next = NULL;

	return sdn;
}
