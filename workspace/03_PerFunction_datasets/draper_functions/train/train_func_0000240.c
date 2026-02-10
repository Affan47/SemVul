source_registry_compare_nodes (GNode *node_a,
                               GNode *node_b)
{
	ESource *source_a = E_SOURCE (node_a->data);
	ESource *source_b = E_SOURCE (node_b->data);
	const gchar *uid_a, *uid_b;

	uid_a = e_source_get_uid (source_a);
	uid_b = e_source_get_uid (source_b);


	if (uid_a == NULL) {
		g_warn_if_reached ();
		uid_a = "";
	}
	if (uid_b == NULL) {
		g_warn_if_reached ();
		uid_b = "";
	}


	if (g_strcmp0 (uid_a, "local-stub") == 0)
		return -1;

	if (g_strcmp0 (uid_b, "local-stub") == 0)
		return 1;


	if (g_str_has_prefix (uid_a, "system-"))
		return -1;

	if (g_str_has_prefix (uid_b, "system-"))
		return 1;

	return e_source_compare_by_display_name (source_a, source_b);
}
