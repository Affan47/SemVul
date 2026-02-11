dna_update_config_event(time_t event_time, void *arg)
{
    Slapi_PBlock *pb = NULL;
    struct configEntry *config_entry = NULL;
    PRCList *list = NULL;


    dna_read_lock();


    if (!g_plugin_started) {
        goto bail;
    }


    if (!PR_CLIST_IS_EMPTY(dna_global_config)) {
        list = PR_LIST_HEAD(dna_global_config);


        if ((pb = slapi_pblock_new()) == NULL)
            goto bail;

        while (list != dna_global_config) {
            config_entry = (struct configEntry *) list;


            if (config_entry->shared_cfg_dn != NULL) {
                int rc = 0;
                Slapi_PBlock *dna_pb = NULL;
                Slapi_DN *sdn = slapi_sdn_new_normdn_byref(config_entry->shared_cfg_dn);
                Slapi_Backend *be = slapi_be_select(sdn);
                slapi_sdn_free(&sdn);
                if (be) {
                    dna_pb = slapi_pblock_new();
                    slapi_pblock_set(dna_pb, SLAPI_BACKEND, be);

                    rc = slapi_back_transaction_begin(dna_pb);
                    if (rc) {
                        slapi_log_error(SLAPI_LOG_FATAL, DNA_PLUGIN_SUBSYSTEM,
                                  "dna_update_config_event: failed to start transaction\n");
                    }
                }

                slapi_lock_mutex(config_entry->lock);


                slapi_delete_internal_set_pb(pb, config_entry->shared_cfg_dn,
                                             NULL, NULL, getPluginID(), 0);


                slapi_delete_internal_pb(pb);


                dna_update_shared_config(config_entry);

                slapi_unlock_mutex(config_entry->lock);
                if (dna_pb) {
                    if (0 == rc) {
                        slapi_back_transaction_commit(dna_pb);
                    }
                    slapi_pblock_destroy(dna_pb);
                }
                slapi_pblock_init(pb);
            }

            list = PR_NEXT_LINK(list);
        }
    }

bail:
    dna_unlock();
    slapi_pblock_destroy(pb);
}
