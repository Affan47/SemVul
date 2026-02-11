legacy_consumer_config_add (Slapi_PBlock *pb, Slapi_Entry* e, Slapi_Entry* entryAfter, int *returncode, char *returntext, void *arg)
{
    int rc;

	rc = legacy_consumer_extract_config(e, returntext);
	if (rc != LDAP_SUCCESS)
	{
		*returncode = rc;
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "Failed to configure legacy replication\n");
		return SLAPI_DSE_CALLBACK_ERROR;
	}

    legacy_consumer_encode_pw(e);

    slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name, "legacy_consumer_config_add: "
                    "successfully configured legacy consumer credentials\n");

	return SLAPI_DSE_CALLBACK_OK;
}
