consumer_connection_extension_constructor (void *object, void *parent)
{
	consumer_connection_extension *ext = (consumer_connection_extension*) slapi_ch_malloc (sizeof (consumer_connection_extension));
	if (ext == NULL)
	{
		slapi_log_error( SLAPI_LOG_PLUGIN, repl_plugin_name, "unable to create replication consumer connection extension - out of memory\n" );
	}
	else
	{
	    ext->is_legacy_replication_dn= 0;
		ext->repl_protocol_version = REPL_PROTOCOL_UNKNOWN;
		ext->replica_acquired = NULL;
		ext->isreplicationsession= 0;
        ext->supplier_ruv = NULL;
		ext->connection = NULL;
		ext->in_use_opid = -1;
		ext->lock = PR_NewLock();
		if (NULL == ext->lock)
		{
			slapi_log_error( SLAPI_LOG_PLUGIN, repl_plugin_name, "unable to create replication consumer connection extension lock - out of memory\n" );

			slapi_ch_free((void **)&ext);
			ext = NULL;
		}
	}

	return ext;
}
