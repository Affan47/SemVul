slapi_modify_internal_set_pb (Slapi_PBlock *pb, const char *dn,
                              LDAPMod **mods, LDAPControl **controls,
                              const char *uniqueid,
                              Slapi_ComponentId *plugin_identity,
                              int operation_flags)
{
	Operation *op;
	PR_ASSERT (pb != NULL);
	if (pb == NULL || dn == NULL || mods == NULL)
	{
		slapi_log_error(SLAPI_LOG_FATAL, NULL,
						"slapi_modify_internal_set_pb: NULL parameter\n");
		return;
	}

	op= internal_operation_new(SLAPI_OPERATION_MODIFY,operation_flags);
	slapi_pblock_set(pb, SLAPI_OPERATION, op);
	slapi_pblock_set(pb, SLAPI_ORIGINAL_TARGET, (void*)dn);
	slapi_pblock_set(pb, SLAPI_MODIFY_MODS, mods);
	slapi_pblock_set(pb, SLAPI_CONTROLS_ARG, controls);
	if (uniqueid)
	{
		slapi_pblock_set(pb, SLAPI_TARGET_UNIQUEID, (void*)uniqueid);
	}
	slapi_pblock_set(pb, SLAPI_PLUGIN_IDENTITY, plugin_identity);
}
