roles_cache_find_roles_in_suffix(Slapi_DN *target_entry_dn, roles_cache_def **list_of_roles)
{
    int rc = -1;
	Slapi_Backend *backend = NULL;

	slapi_log_error(SLAPI_LOG_PLUGIN,
					ROLES_PLUGIN_SUBSYSTEM, "--> roles_cache_find_roles_in_suffix\n");

	*list_of_roles = NULL;
	backend = slapi_mapping_tree_find_backend_for_sdn(target_entry_dn);
	if ( (backend != NULL) && !slapi_be_is_flag_set(backend,SLAPI_BE_FLAG_REMOTE_DATA) )
	{
		Slapi_DN *suffix = roles_cache_get_top_suffix((Slapi_DN *)slapi_be_getsuffix(backend, 0));
		roles_cache_def *current_role = roles_list;


		while ( (current_role != NULL) && (suffix != NULL) )
		{
			if ( slapi_sdn_compare(current_role->suffix_dn, suffix) == 0 )
			{
				*list_of_roles = current_role;

				slapi_sdn_free(&suffix);
				return 0;
			}
			else
			{
				current_role = current_role->next;
			}
		}
		if ( suffix != NULL )
		{
			slapi_sdn_free(&suffix);
		}


		return rc;
	}

	slapi_log_error(SLAPI_LOG_PLUGIN,
					ROLES_PLUGIN_SUBSYSTEM, "<-- roles_cache_find_roles_in_suffix\n");
    return rc;
}
