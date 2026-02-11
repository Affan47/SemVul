orte_sstore_base_local_snapshot_info_destruct( orte_sstore_base_local_snapshot_info_t *snapshot)
{
    snapshot->process_name.jobid  = 0;
    snapshot->process_name.vpid   = 0;

    if( NULL != snapshot->crs_comp ) {
        free(snapshot->crs_comp);
        snapshot->crs_comp = NULL;
    }

    if( NULL != snapshot->compress_comp ) {
        free(snapshot->compress_comp);
        snapshot->compress_comp = NULL;
    }

    if( NULL != snapshot->compress_postfix ) {
        free(snapshot->compress_postfix);
        snapshot->compress_postfix = NULL;
    }

    if( NULL != snapshot->start_time ) {
        free(snapshot->start_time);
        snapshot->start_time = NULL;
    }

    if( NULL != snapshot->end_time ) {
        free(snapshot->end_time);
        snapshot->end_time = NULL;
    }
}
