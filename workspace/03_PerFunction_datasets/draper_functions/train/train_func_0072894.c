netinfo_validate_domain (Netinfo * netinfo)
{
	gchar *domain;
	gchar *primary = NULL;
	gchar *secondary = NULL;

	domain = g_strdup (netinfo_get_host (netinfo));
	g_strstrip (domain);

	if (! strcmp (domain, "")) {
		primary = g_strdup (_("A domain address was not specified"));
		secondary = g_strdup (_("Please enter a valid domain address and try again."));
	}
	g_free (domain);

	if (primary) {
		netinfo_error_message (netinfo, primary, secondary);
		g_free (primary);
		if (secondary)
			g_free (secondary);
		return FALSE;
	}

	return TRUE;
}
