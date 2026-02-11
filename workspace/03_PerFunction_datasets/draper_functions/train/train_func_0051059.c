generate_unique_cookie (UrfSessionChecker *logind)
{
	UrfInhibitor *inhibitor;
	guint cookie;

	do {
		cookie = g_random_int_range (1, G_MAXINT);
		inhibitor = find_inhibitor_by_cookie (logind, cookie);
	} while (inhibitor != NULL);

	return cookie;
}
