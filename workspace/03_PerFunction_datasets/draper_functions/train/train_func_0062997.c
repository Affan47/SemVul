roles_cache_role_def_delete(roles_cache_def *role_def)
{
	roles_cache_def *current = roles_list;
	roles_cache_def *previous = NULL;

	slapi_log_error(SLAPI_LOG_PLUGIN,
					ROLES_PLUGIN_SUBSYSTEM, "--> roles_cache_role_def_delete\n");

	while ( current!= NULL )
	{
		if ( slapi_sdn_compare(current->suffix_dn, role_def->suffix_dn) == 0 )
		{
			if ( previous== NULL )
			{
				roles_list = current->next;
			}
			else
			{
				previous->next = current->next;
			}
			slapi_lock_mutex(role_def->change_lock);
			role_def->keeprunning = 0;
			slapi_notify_condvar(role_def->something_changed, 1 );
			slapi_unlock_mutex(role_def->change_lock);
			break;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
	slapi_log_error(SLAPI_LOG_PLUGIN,
					ROLES_PLUGIN_SUBSYSTEM, "<-- roles_cache_role_def_delete\n");
}
