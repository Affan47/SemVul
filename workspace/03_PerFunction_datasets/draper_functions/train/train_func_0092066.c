cluster_disconnect_cpg(crm_cluster_t *cluster)
{
    pcmk_cpg_handle = 0;
    if (cluster->cpg_handle) {
        crm_trace("Disconnecting CPG");
        cpg_leave(cluster->cpg_handle, &cluster->group);
        cpg_finalize(cluster->cpg_handle);
        cluster->cpg_handle = 0;

    } else {
        crm_info("No CPG connection");
    }
}
