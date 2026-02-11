get_id (MonoDomain *domain, IdType type, gpointer val)
{
	Id *id;
	AgentDomainInfo *info;

	if (val == NULL)
		return 0;

	info = get_agent_domain_info (domain);

	dbg_lock ();

	if (info->val_to_id [type] == NULL)
		info->val_to_id [type] = g_hash_table_new (mono_aligned_addr_hash, NULL);

	id = (Id *)g_hash_table_lookup (info->val_to_id [type], val);
	if (id) {
		dbg_unlock ();
		return id->id;
	}

	id = g_new0 (Id, 1);

	id->id = ids [type]->len + 1;
	id->domain = domain;
	id->data.val = val;

	g_hash_table_insert (info->val_to_id [type], val, id);
	g_ptr_array_add (ids [type], id);

	dbg_unlock ();

	return id->id;
}
