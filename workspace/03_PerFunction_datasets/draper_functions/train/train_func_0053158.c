multimaster_set_local_purl()
{
    int rc = 0;
    Slapi_Entry **entries;
    Slapi_PBlock *pb = NULL;

    pb = slapi_pblock_new ();

	slapi_search_internal_set_pb (pb, "cn=config", LDAP_SCOPE_BASE,
		"objectclass=*", purl_attrs, 0, NULL, NULL,
		repl_get_plugin_identity (PLUGIN_MULTIMASTER_REPLICATION), 0);
    slapi_search_internal_pb (pb);
    slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_RESULT, &rc);
    if (rc != 0)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "multimaster_set_local_purl: "
			"unable to read server configuration: error %d\n", rc);
	}
	else
	{
		slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_SEARCH_ENTRIES, &entries);
		if (NULL == entries || NULL == entries[0])
		{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "multimaster_set_local_purl: "
			"server configuration missing\n");
			rc = -1;
		}
		else
		{
			char *host = slapi_entry_attr_get_charptr(entries[0], "nsslapd-localhost");
			char *port = slapi_entry_attr_get_charptr(entries[0], "nsslapd-port");
			char *sslport = slapi_entry_attr_get_charptr(entries[0], "nsslapd-secureport");
			if (host == NULL || ((port == NULL && sslport == NULL)))
			{
				slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
					"multimaster_set_local_purl: invalid server "
					"configuration\n");
			}
			else
			{
				if(slapi_is_ipv6_addr(host)){

					local_purl = slapi_ch_smprintf("ldap://[%s]:%s", host, port);
				} else {
					local_purl = slapi_ch_smprintf("ldap://%s:%s", host, port);
				}
			}


			slapi_ch_free ((void**)&host);
			slapi_ch_free ((void**)&port);
			slapi_ch_free ((void**)&sslport);
		}
	}
    slapi_free_search_results_internal(pb);
    slapi_pblock_destroy (pb);

	return rc;
}
