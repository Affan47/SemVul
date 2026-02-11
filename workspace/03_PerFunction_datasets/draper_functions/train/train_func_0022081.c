orte_sstore_base_global_snapshot_info_construct(orte_sstore_base_global_snapshot_info_t *snapshot)
{
    OBJ_CONSTRUCT(&(snapshot->local_snapshots), opal_list_t);

    snapshot->ss_handle  = ORTE_SSTORE_HANDLE_INVALID;

    snapshot->start_time = NULL;
    snapshot->end_time   = NULL;

    snapshot->seq_num = -1;

    snapshot->num_seqs = 0;
    snapshot->all_seqs = NULL;
    snapshot->basedir = NULL;
    snapshot->reference = NULL;
    snapshot->amca_param = NULL;
    snapshot->metadata_filename = NULL;
}
