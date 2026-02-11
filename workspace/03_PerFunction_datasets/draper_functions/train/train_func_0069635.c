ruvAddIndexReplicaNoCSN (RUV *ruv, ReplicaId rid, const char *replica_purl, int index)
{
    RUVElement *replica;

	PR_ASSERT (NULL != ruv);


	replica = (RUVElement *)slapi_ch_calloc (1, sizeof (RUVElement));
	if (replica == NULL)
	{
		slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name,
						"ruvAddIndexReplicaNoCSN: memory allocation failed\n");
		return NULL;
	}

	replica->rid = rid;
	replica->replica_purl = slapi_ch_strdup(replica_purl);
    replica->csnpl = csnplNew ();

	dl_add_index (ruv->elements, replica, index);

	return replica;
}
