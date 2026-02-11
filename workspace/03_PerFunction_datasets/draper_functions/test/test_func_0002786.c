tombstone_to_glue_resolve_parent (
	Slapi_PBlock *pb,
	const char *sessionid,
	const Slapi_DN *parentdn,
	const char *parentuniqueid,
	CSN *opcsn)
{

	if(!slapi_sdn_isempty(parentdn) && parentuniqueid!=NULL)
	{
		int op_result;
	    Slapi_PBlock *newpb= slapi_pblock_new();
	    slapi_search_internal_set_pb(
	    			newpb,
	    			slapi_sdn_get_dn(parentdn),
	    			LDAP_SCOPE_BASE,
					"objectclass=*",
					NULL,
					0,
					NULL,
					parentuniqueid,
					repl_get_plugin_identity(PLUGIN_MULTIMASTER_REPLICATION),
					0);
		slapi_search_internal_pb(newpb);
	    slapi_pblock_get(newpb, SLAPI_PLUGIN_INTOP_RESULT, &op_result);
		switch(op_result)
		{
		case LDAP_SUCCESS:
			{
			Slapi_Entry **entries= NULL;

			slapi_pblock_get(newpb, SLAPI_PLUGIN_INTOP_SEARCH_ENTRIES, &entries);
			if(entries!=NULL && entries[0]!=NULL)
			{
				if(is_tombstone_entry(entries[0]))
				{
					tombstone_to_glue (pb, sessionid, entries[0], parentdn, REASON_RESURRECT_ENTRY, opcsn);
				}
			}
			else
			{

			}
			}
			break;
		default:


			break;
		}
		slapi_free_search_results_internal (newpb);
		slapi_pblock_destroy(newpb);
	}
	return 0;
}
