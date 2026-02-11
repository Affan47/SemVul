tcp_init(struct mca_oob_tcp_module_t *md)
{
    mca_oob_tcp_module_t *mod = (mca_oob_tcp_module_t*)md;


    OBJ_CONSTRUCT(&mod->peers, opal_hash_table_t);
    opal_hash_table_init(&mod->peers, 32);
    mod->ev_active = false;

    if (orte_oob_base.use_module_threads) {


        opal_output_verbose(2, orte_oob_base_framework.framework_output,
                            "%s STARTING TCP PROGRESS THREAD ON INTERFACE %s",
                            ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), mod->if_name);
        mod->ev_base = opal_event_base_create();

        OBJ_CONSTRUCT(&mod->progress_thread, opal_thread_t);

        mod->progress_thread.t_run = progress_thread_engine;
        mod->progress_thread.t_arg = mod;
        mod->ev_active = true;
        if (OPAL_SUCCESS != opal_thread_start(&mod->progress_thread)) {
            opal_output(0, "%s progress thread failed to start for interface %s",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), mod->if_name);
        }
    }
}
