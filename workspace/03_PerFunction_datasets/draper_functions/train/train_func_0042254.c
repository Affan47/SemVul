orte_snapc_base_quiesce_construct(orte_snapc_base_quiesce_t *quiesce)
{
    quiesce->epoch         = -1;
    quiesce->snapshot      = NULL;
    quiesce->ss_handle     = ORTE_SSTORE_HANDLE_INVALID;
    quiesce->ss_snapshot   = NULL;
    quiesce->handle        = NULL;
    quiesce->target_dir    = NULL;
    quiesce->crs_name      = NULL;
    quiesce->cmdline       = NULL;
    quiesce->cr_state      = OPAL_CRS_NONE;
    quiesce->checkpointing = false;
    quiesce->restarting    = false;

    quiesce->migrating     = false;
    quiesce->num_migrating = 0;
    OBJ_CONSTRUCT(&(quiesce->migrating_procs), opal_pointer_array_t);
    opal_pointer_array_init(&(quiesce->migrating_procs), 8, INT32_MAX, 8);
}
