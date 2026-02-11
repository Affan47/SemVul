get_ldap_library_info (void)
{
	LDAPAPIInfo info;
	LDAP *ldap;

	ldap = ldap_init (NULL, 0);
	if (ldap == NULL) {
		g_warning ("couldn't create LDAP* for getting at the client lib api info");
		return;
	}

	info.ldapai_info_version = LDAP_API_INFO_VERSION;

	if (LDAP_OPT_SUCCESS != ldap_get_option (ldap, LDAP_OPT_API_INFO, &info)) {
		g_warning ("couldn't get ldap api info");
	}
	else {
		gint i;
		if (enable_debug) {
			g_message (
				"libldap vendor/version: %s %2d.%02d.%02d",
				info.ldapai_vendor_name,
				info.ldapai_vendor_version / 10000,
				(info.ldapai_vendor_version % 10000) / 1000,
				info.ldapai_vendor_version % 1000);

			g_message ("library extensions present:");
		}


		for (i = 0; info.ldapai_extensions[i]; i++) {
			gchar *extension = info.ldapai_extensions[i];
			if (enable_debug)
				g_message ("%s", extension);
			ldap_memfree (extension);
		}
		ldap_memfree (info.ldapai_extensions);
		ldap_memfree (info.ldapai_vendor_name);
	}

	ldap_unbind (ldap);
}
