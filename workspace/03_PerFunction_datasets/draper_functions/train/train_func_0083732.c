ldap_rebind(LDAP *ld, LDAP_CONST char *url,
		       UNUSED ber_tag_t request, UNUSED ber_int_t msgid,
		       void *params )
{
	ldap_instance	*inst = params;

	DEBUG("  [%s] rebind to URL %s", inst->xlat_name,url);
	return ldap_bind_s(ld, inst->login, inst->password, LDAP_AUTH_SIMPLE);
}
