plugin_add_descriptive_attributes( Slapi_Entry *e, struct slapdplugin *plugin )
{
	int		status = 0;

	if ( NULL == plugin ) {
		int					i;
		const Slapi_DN		*ednp = slapi_entry_get_sdn_const( e );
		Slapi_DN			pdn;
		struct slapdplugin	*plugtmp;

		for( i = 0; NULL == plugin && i < PLUGIN_LIST_GLOBAL_MAX; ++i )
		{
			for ( plugtmp = global_plugin_list[i]; NULL == plugin && plugtmp;
						plugtmp = plugtmp->plg_next)
			{
				slapi_sdn_init_normdn_byref( &pdn, plugtmp->plg_dn );
				if ( 0 == slapi_sdn_compare( &pdn, ednp ))
				{
					plugin = plugtmp;
				}
				slapi_sdn_done( &pdn );
			}
		}

		if ( NULL == plugin )
		{


			LDAPDebug(LDAP_DEBUG_PLUGIN,
					"Warning: couldn't find plugin %s in global list. "
					"Adding default descriptive values.\n",
					slapi_entry_get_dn_const(e), 0, 0 );
		}
	}


	if (add_plugin_description(e, ATTR_PLUGIN_PLUGINID,
	                           plugin ? plugin->plg_desc.spd_id : NULL))
	{
		status = 1;
	}

	if (add_plugin_description(e, ATTR_PLUGIN_VERSION,
	                           plugin ? plugin->plg_desc.spd_version : NULL))
	{
		status = 1;
	}

	if (add_plugin_description(e, ATTR_PLUGIN_VENDOR,
	                           plugin ? plugin->plg_desc.spd_vendor: NULL))
	{
		status = 1;
	}

	if (add_plugin_description(e, ATTR_PLUGIN_DESC,
	                           plugin ? plugin->plg_desc.spd_description : NULL))
	{
		status = 1;
	}

	return status;
}
