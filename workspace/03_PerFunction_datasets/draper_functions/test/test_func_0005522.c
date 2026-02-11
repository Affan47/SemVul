get_cluster_type(void)
{
    bool detected = FALSE;
    const char *cluster = NULL;


    if (cluster_type != pcmk_cluster_unknown) {
        return cluster_type;
    }

    cluster = getenv("HA_cluster_type");

#if SUPPORT_HEARTBEAT

    if(cluster == NULL) {
        ll_cluster_t *hb;
        ll_cluster_t *(*new_cluster) (const char *llctype) = find_library_function(
            &hb_library, HEARTBEAT_LIBRARY, "ll_cluster_new", 1);

        hb = (*new_cluster) ("heartbeat");

        crm_debug("Testing with Heartbeat");
        if (hb->llc_ops->signon(hb, crm_system_name) == HA_OK) {
            hb->llc_ops->signoff(hb, FALSE);

            cluster_type = pcmk_cluster_heartbeat;
            detected = TRUE;
            goto done;
        }
    }
#endif

#if SUPPORT_COROSYNC

    if(cluster == NULL) {
        crm_debug("Testing with Corosync");
        cluster_type = find_corosync_variant();
        if (cluster_type != pcmk_cluster_unknown) {
            detected = TRUE;
            goto done;
        }
    }
#endif


    crm_info("Verifying cluster type: '%s'", cluster?cluster:"-unspecified-");
    if (cluster == NULL) {

#if SUPPORT_HEARTBEAT
    } else if (safe_str_eq(cluster, "heartbeat")) {
        cluster_type = pcmk_cluster_heartbeat;
#endif

#if SUPPORT_COROSYNC
    } else if (safe_str_eq(cluster, "openais")
               || safe_str_eq(cluster, "classic openais (with plugin)")) {
        cluster_type = pcmk_cluster_classic_ais;

    } else if (safe_str_eq(cluster, "corosync")) {
        cluster_type = pcmk_cluster_corosync;
#endif

#if SUPPORT_CMAN
    } else if (safe_str_eq(cluster, "cman")) {
        cluster_type = pcmk_cluster_cman;
#endif

    } else {
        cluster_type = pcmk_cluster_invalid;
        goto done;
    }

  done:
    if (cluster_type == pcmk_cluster_unknown) {
        crm_notice("Could not determin the current cluster type");

    } else if (cluster_type == pcmk_cluster_invalid) {
        crm_notice("This installation does not support the '%s' cluster infrastructure: terminating.",
                   cluster);
        crm_exit(DAEMON_RESPAWN_STOP);

    } else {
        crm_info("%s an active '%s' cluster", detected?"Detected":"Assuming", name_for_cluster_type(cluster_type));
    }

    return cluster_type;
}
