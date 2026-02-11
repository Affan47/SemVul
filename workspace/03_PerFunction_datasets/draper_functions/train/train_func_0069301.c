gfarm_ldap_xattr_info_make_dn(void *vkey)
{
	struct gfarm_ldap_xattr_get_info_key *key = vkey;
	char *dn;

	GFARM_MALLOC_ARRAY(dn, strlen(gfarm_ldap_xattr_info_ops.dn_template) +
		strlen(key->attrname) + INT64STRLEN
		+ strlen(gfarm_ldap_base_dn) + 1);
	if (dn == NULL) {
		gflog_debug(GFARM_MSG_1002135,
			"allocation of string 'dn' failed");
		return (NULL);
	}
	sprintf(dn, gfarm_ldap_xattr_info_ops.dn_template,
	    key->attrname, key->inumber, gfarm_ldap_base_dn);
	return (dn);
}
