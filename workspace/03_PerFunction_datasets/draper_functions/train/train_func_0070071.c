slapi_seq_callback( const char *ibase,
                    int type,
                    char *attrname,
                    char *val,
                    char **attrs,
                    int attrsonly,
                    void *callback_data,
                    LDAPControl **controls,
                    plugin_result_callback res_callback,
                    plugin_search_entry_callback srch_callback,
                    plugin_referral_entry_callback ref_callback)
{
	int r;
    Slapi_PBlock pb;

	if (ibase == NULL)
	{
		slapi_log_error(SLAPI_LOG_FATAL, NULL,
						"slapi_seq_callback: NULL parameter\n");
		return -1;
	}

	pblock_init(&pb);

    slapi_seq_internal_set_pb(&pb, (char *)ibase, type, attrname, val, attrs, attrsonly, controls,
		plugin_get_default_component_id(), 0);

    r= seq_internal_callback_pb (&pb, callback_data, res_callback, srch_callback, ref_callback);
	pblock_done(&pb);
	return r;
}
