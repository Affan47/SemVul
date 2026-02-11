replica_enable_replication (Replica *r)
{
    int rc;

    PR_ASSERT(r);


    PR_Lock(r->agmt_lock);


    rc = replica_reload_ruv (r);
    if (rc) {
        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "replica_enable_replication: "
                        "reloading ruv failed\n");

    }


    if (!replica_is_state_flag_set(r, REPLICA_TOTAL_IN_PROGRESS)){

        start_agreements_for_replica (r, PR_TRUE);


        replica_set_enabled (r, PR_TRUE);
    }


    replica_relinquish_exclusive_access(r, 0, 0);

    replica_set_state_flag(r, REPLICA_AGREEMENTS_DISABLED, PR_TRUE );
    PR_Unlock(r->agmt_lock);

    slapi_log_error(SLAPI_LOG_REPL, repl_plugin_name, "replica_enable_replication: "
                    "replica %s is relinquished\n",
                    slapi_sdn_get_ndn (replica_get_root (r)));
}
