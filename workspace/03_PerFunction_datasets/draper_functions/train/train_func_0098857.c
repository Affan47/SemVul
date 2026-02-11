agmtlist_delete_callback(Slapi_PBlock *pb, Slapi_Entry *e, Slapi_Entry *entryAfter,
	int *returncode, char *returntext, void *arg)
{
	Repl_Agmt *ra;
	Object *ro;

	slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "agmt_delete: begin\n");
	ro = objset_find(agmt_set, agmt_dn_cmp, (const void *)slapi_entry_get_sdn_const(e));
	ra = (NULL == ro) ? NULL : (Repl_Agmt *)object_get_data(ro);
	if (NULL == ra)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "agmtlist_delete: "
			"Tried to delete replication agreement \"%s\", but no such "
			"agreement was configured.\n", slapi_sdn_get_dn(slapi_entry_get_sdn_const(e)));
	}
	else
	{
		agmt_stop(ra);
		object_release(ro);
		objset_remove_obj(agmt_set, ro);
	}
	*returncode = LDAP_SUCCESS;
	return SLAPI_DSE_CALLBACK_OK;
}
