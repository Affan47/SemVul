free_connman_wispr_portal(gpointer data)
{
	struct connman_wispr_portal *wispr_portal = data;

	DBG("");

	if (wispr_portal == NULL)
		return;

	free_connman_wispr_portal_context(wispr_portal->ipv4_context);
	free_connman_wispr_portal_context(wispr_portal->ipv6_context);

	g_free(wispr_portal);
}
