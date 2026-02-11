IsValidOperation (const slapi_operation_parameters *op)
{
	if (op == NULL)
    {
        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"IsValidOperation: NULL operation\n");
        return PR_FALSE;
    }

    if (op->csn == NULL)
    {
        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"IsValidOperation: NULL operation CSN\n");
        return PR_FALSE;
    }

    if (op->target_address.uniqueid == NULL)
    {
        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"IsValidOperation: NULL entry uniqueid\n");
        return PR_FALSE;
    }

    if (op->target_address.sdn == NULL)
    {
        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"IsValidOperation: NULL entry DN\n");
        return PR_FALSE;
    }

	switch (op->operation_type)
	{
		case SLAPI_OPERATION_ADD:		if (op->p.p_add.target_entry == NULL)
                                        {
                                            slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						                    "IsValidOperation: NULL entry for add operation\n");
											return PR_FALSE;
                                        }
										else
											break;

		case SLAPI_OPERATION_MODIFY:	if (op->p.p_modify.modify_mods == NULL ||
										    op->p.p_modify.modify_mods[0] == NULL)
                                        {
                                            slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						                    "IsValidOperation: NULL mods for modify operation\n");
											return PR_FALSE;
                                        }
										else
											break;

		case SLAPI_OPERATION_MODRDN:	if (op->p.p_modrdn.modrdn_mods == NULL ||
											op->p.p_modrdn.modrdn_mods[0] == NULL)
										{
                                            slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						                    "IsValidOperation: NULL mods for modrdn operation\n");
											return PR_FALSE;
                                        }
										if (op->p.p_modrdn.modrdn_newrdn == NULL)
										{
                                            slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						                    "IsValidOperation: NULL new rdn for modrdn operation\n");
											return PR_FALSE;
                                        }
										else
											break;

		case SLAPI_OPERATION_DELETE:	break;

		default:						return PR_FALSE;
	}

	return PR_TRUE;
}
