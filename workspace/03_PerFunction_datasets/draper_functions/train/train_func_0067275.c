replica_new_from_entry (Slapi_Entry *e, char *errortext, PRBool is_add_operation)
{
	int rc = 0;
	Replica *r;
	char *repl_name = NULL;

	if (e == NULL)
	{
		if (NULL != errortext)
		{
			PR_snprintf(errortext, SLAPI_DSE_RETURNTEXT_SIZE, "NULL entry");
		}
		return NULL;
	}

	r = (Replica *)slapi_ch_calloc(1, sizeof(Replica));

	if (!r)
	{
		if (NULL != errortext)
		{
			PR_snprintf(errortext, SLAPI_DSE_RETURNTEXT_SIZE, "Out of memory");
		}
		rc = -1;
		goto done;
	}

	if ((r->repl_lock = PR_NewLock()) == NULL)
	{
		if (NULL != errortext)
		{
            PR_snprintf(errortext, SLAPI_DSE_RETURNTEXT_SIZE, "failed to create replica lock");
		}
		rc = -1;
		goto done;
	}

	if ((r->agmt_lock = PR_NewLock()) == NULL)
	{
		if (NULL != errortext)
		{
            PR_snprintf(errortext, SLAPI_DSE_RETURNTEXT_SIZE, "failed to create replica lock");
		}
		rc = -1;
		goto done;
	}


	r->protocol_timeout = slapi_counter_new();
	r->backoff_min = slapi_counter_new();
	r->backoff_max = slapi_counter_new();


    rc = _replica_init_from_config (r, e, errortext);
    if (rc != 0)
	{
		goto done;
	}


	rc = _replica_configure_ruv (r, PR_FALSE);
	if (rc != 0)
	{
		goto done;
	}


	PR_ASSERT (object_get_data (r->repl_ruv));

	if (is_add_operation)
	{


		rc = _replica_update_entry (r, e, errortext);
	}
	else
	{


	}
    if (rc != 0)
		goto done;


	repl_name = slapi_ch_strdup (r->repl_name);
	r->repl_eqcxt_rs = slapi_eq_repeat(replica_update_state, repl_name,
                                       current_time () + START_UPDATE_DELAY, RUV_SAVE_INTERVAL);

	if (r->tombstone_reap_interval > 0)
	{


		repl_name = slapi_ch_strdup (r->repl_name);
		r->repl_eqcxt_tr = slapi_eq_repeat(eq_cb_reap_tombstones, repl_name,
										   current_time() + r->tombstone_reap_interval,
										   1000 * r->tombstone_reap_interval);
	}

    if (r->legacy_consumer)
    {
        legacy_consumer_init_referrals (r);
        slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name, "replica_new_from_entry: "
                        "replica for %s was configured as legacy consumer\n",
                        slapi_sdn_get_dn(r->repl_root));
    }

    replica_check_for_tasks(r, e);

done:
    if (rc != 0 && r)
	{
        replica_destroy ((void**)&r);
	}

    return r;
}
