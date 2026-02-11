send_type_load (MonoClass *klass)
{
	gboolean type_load = FALSE;
	MonoDomain *domain = mono_domain_get ();
	AgentDomainInfo *info = NULL;

	info = get_agent_domain_info (domain);

	mono_loader_lock ();

	if (!g_hash_table_lookup (info->loaded_classes, klass)) {
		type_load = TRUE;
		g_hash_table_insert (info->loaded_classes, klass, klass);
	}

	mono_loader_unlock ();

	if (type_load)
		emit_type_load (klass, klass, NULL);
}
