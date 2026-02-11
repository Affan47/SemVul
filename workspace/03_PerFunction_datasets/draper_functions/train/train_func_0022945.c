pref_setldap(const char *p)
{
	if (pref_ldap && strcmp(p, pref_ldap) == 0)
		return;

	if (pref_ldap)	free(pref_ldap);
	pref_ldap=strdup(p);
	if (!pref_ldap)	enomem();
	pref_update();
}
