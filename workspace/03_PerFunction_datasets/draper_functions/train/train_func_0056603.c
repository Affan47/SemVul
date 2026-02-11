ldif_ldapmod4line(char *action, char *ad)
{
	LDAPMod *m;
	int op;

 	if (!strcmp(action, "add"))
		op = LDAP_MOD_ADD;
	else if (!strcmp(action, "delete"))
		op = LDAP_MOD_DELETE;
	else if (!strcmp(action, "replace"))
		op = LDAP_MOD_REPLACE;
	else {
		fputs(action, stderr);
		fputs("Error: Invalid change marker.\n", stderr);
		return 0;
	}

	m = xalloc(sizeof(LDAPMod));
	m->mod_op = op | LDAP_MOD_BVALUES;
	m->mod_type = xdup(ad);
	return m;
}
