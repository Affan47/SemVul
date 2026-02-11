consumer_connection_extension_destructor (void *ext, void *object, void *parent)
{
	PRUint64 connid = 0;
	if (ext)
	{


		consumer_connection_extension *connext = (consumer_connection_extension *)ext;
		if (NULL != connext->replica_acquired)
		{
            Replica *r = object_get_data ((Object*)connext->replica_acquired);

			if (REPL_PROTOCOL_50_TOTALUPDATE == connext->repl_protocol_version)
			{
				Slapi_PBlock *pb = slapi_pblock_new();
				const Slapi_DN *repl_root_sdn = replica_get_root(r);
				PR_ASSERT(NULL != repl_root_sdn);
				if (NULL != repl_root_sdn)
				{
					slapi_pblock_set(pb, SLAPI_CONNECTION, connext->connection);
					slapi_pblock_set(pb, SLAPI_TARGET_SDN, (void*)repl_root_sdn);
					slapi_pblock_get(pb, SLAPI_CONN_ID, &connid);
					slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name,
									"Aborting total update in progress for replicated "
									"area %s connid=%" NSPRIu64 "\n", slapi_sdn_get_dn(repl_root_sdn),
									(long long unsigned int)connid);
					slapi_stop_bulk_import(pb);
				}
				else
				{
					slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"consumer_connection_extension_destructor: can't determine root "
						"of replicated area.\n");
				}
				slapi_pblock_destroy(pb);


				replica_set_tombstone_reap_stop(r, PR_FALSE);
			}
			replica_relinquish_exclusive_access(r, connid, -1);
            object_release ((Object*)connext->replica_acquired);
			connext->replica_acquired = NULL;
		}

        if (connext->supplier_ruv)
        {
            ruv_destroy ((RUV **)&connext->supplier_ruv);
        }

        if (connext->lock)
        {
            PR_DestroyLock(connext->lock);
            connext->lock = NULL;
        }

        connext->in_use_opid = -1;

		connext->connection = NULL;
		slapi_ch_free((void **)&ext);
	}
}
