source_registry_server_allow_auth_prompt_all_cb (EDBusSourceManager *interface,
                                                 GDBusMethodInvocation *invocation,
                                                 ESourceRegistryServer *server)
{
	GList *list, *link;

	list = e_source_registry_server_list_sources (server, NULL);

	for (link = list; link != NULL; link = g_list_next (link))
		e_server_side_source_set_allow_auth_prompt (
			E_SERVER_SIDE_SOURCE (link->data), TRUE);

	g_list_free_full (list, (GDestroyNotify) g_object_unref);

	e_dbus_source_manager_complete_allow_auth_prompt_all (
		interface, invocation);

	return TRUE;
}
