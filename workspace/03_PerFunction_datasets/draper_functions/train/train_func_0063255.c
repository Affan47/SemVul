dna_start(Slapi_PBlock * pb)
{
    Slapi_DN *pluginsdn = NULL;
    const char *plugindn = NULL;

    slapi_log_error(SLAPI_LOG_TRACE, DNA_PLUGIN_SUBSYSTEM,
                    "--> dna_start\n");


    if (g_plugin_started) {
        goto done;
    }

    g_dna_cache_lock = slapi_new_rwlock();

    if (!g_dna_cache_lock) {
        slapi_log_error(SLAPI_LOG_FATAL, DNA_PLUGIN_SUBSYSTEM,
                        "dna_start: lock creation failed\n");

        return DNA_FAILURE;
    }


    slapi_pblock_get(pb, SLAPI_TARGET_SDN, &pluginsdn);
    if (NULL == pluginsdn || 0 == slapi_sdn_get_ndn_len(pluginsdn)) {
        slapi_log_error(SLAPI_LOG_PLUGIN, DNA_PLUGIN_SUBSYSTEM,
                        "dna_start: had to use hard coded config dn\n");
        plugindn = DNA_DN;
    } else {
        plugindn = slapi_sdn_get_dn(pluginsdn);
        slapi_log_error(SLAPI_LOG_PLUGIN, DNA_PLUGIN_SUBSYSTEM,
                        "dna_start: config at %s\n", plugindn);

    }

    setPluginDN(plugindn);


    if (dna_load_host_port() != DNA_SUCCESS) {
        slapi_log_error(SLAPI_LOG_FATAL, DNA_PLUGIN_SUBSYSTEM,
                        "dna_start: unable to load host and port information\n");
    }


    dna_global_config = (PRCList *)
        slapi_ch_calloc(1, sizeof(struct configEntry));
    PR_INIT_CLIST(dna_global_config);

    if (dna_load_plugin_config(pb, 1) != DNA_SUCCESS) {
        slapi_log_error(SLAPI_LOG_FATAL, DNA_PLUGIN_SUBSYSTEM,
                        "dna_start: unable to load plug-in configuration\n");
        return DNA_FAILURE;
    }

    g_plugin_started = 1;
    slapi_log_error(SLAPI_LOG_PLUGIN, DNA_PLUGIN_SUBSYSTEM,
                    "dna: ready for service\n");
    slapi_log_error(SLAPI_LOG_TRACE, DNA_PLUGIN_SUBSYSTEM,
                    "<-- dna_start\n");

done:
    return DNA_SUCCESS;
}
