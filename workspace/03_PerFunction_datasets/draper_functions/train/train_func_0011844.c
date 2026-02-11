slapi_search_internal_set_pb_ext (Slapi_PBlock *pb, Slapi_DN *sdn,
                                  int scope, const char *filter, char **attrs,
                                  int attrsonly, LDAPControl **controls,
                                  const char *uniqueid,
                                  Slapi_ComponentId *plugin_identity,
                                  int operation_flags)
{
	Operation *op;
	char **tmp_attrs = NULL;
	if (pb == NULL || sdn == NULL)
	{
		slapi_log_error(SLAPI_LOG_FATAL, NULL,
		                "slapi_search_internal_set_pb: NULL parameter\n");
		return;
	}

	op= internal_operation_new(SLAPI_OPERATION_SEARCH,operation_flags);
	slapi_pblock_set(pb, SLAPI_OPERATION, op);
	slapi_pblock_set(pb, SLAPI_ORIGINAL_TARGET_DN,
	                 (void *)slapi_sdn_get_udn(sdn));
	slapi_pblock_set(pb, SLAPI_TARGET_SDN, (void *)sdn);
	slapi_pblock_set(pb, SLAPI_SEARCH_SCOPE, &scope);
	slapi_pblock_set(pb, SLAPI_SEARCH_STRFILTER, (void*)filter);
	slapi_pblock_set(pb, SLAPI_CONTROLS_ARG, controls);

	tmp_attrs = slapi_ch_array_dup(attrs);
	slapi_pblock_set(pb, SLAPI_SEARCH_ATTRS, tmp_attrs);
	slapi_pblock_set(pb, SLAPI_SEARCH_ATTRSONLY, &attrsonly);
	if (uniqueid)
	{
		slapi_pblock_set(pb, SLAPI_TARGET_UNIQUEID, (void*)uniqueid);
	}
	slapi_pblock_set(pb, SLAPI_PLUGIN_IDENTITY, (void*)plugin_identity);
}
