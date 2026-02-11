defaults_free_searchdns(struct ldap_searchdn *sdn)
{
	struct ldap_searchdn *this = sdn;
	struct ldap_searchdn *next;

	while (this) {
		next = this->next;
		free(this->basedn);
		free(this);
		this = next;
	}

	return;
}
