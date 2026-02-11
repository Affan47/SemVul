pcmk_cpg_dispatch(gpointer user_data)
{
    int rc = 0;
    crm_cluster_t *cluster = (crm_cluster_t*) user_data;

    rc = cpg_dispatch(cluster->cpg_handle, CS_DISPATCH_ALL);
    if (rc != CS_OK) {
        crm_err("Connection to the CPG API failed: %s (%d)", ais_error2text(rc), rc);
        cluster->cpg_handle = 0;
        return -1;

    } else if(cpg_evicted) {
        crm_err("Evicted from CPG membership");
        return -1;
    }
    return 0;
}
