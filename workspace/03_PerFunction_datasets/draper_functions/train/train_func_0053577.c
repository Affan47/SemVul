ompi_proc_init(void)
{
    ompi_vpid_t i;
#if OPAL_ENABLE_HETEROGENEOUS_SUPPORT
    int ret;
#endif

    OBJ_CONSTRUCT(&ompi_proc_list, opal_list_t);
    OBJ_CONSTRUCT(&ompi_proc_lock, opal_mutex_t);


    for( i = 0; i < ompi_process_info.num_procs; i++ ) {
        ompi_proc_t *proc = OBJ_NEW(ompi_proc_t);
        opal_list_append(&ompi_proc_list, (opal_list_item_t*)proc);

        proc->proc_name.jobid = OMPI_PROC_MY_NAME->jobid;
        proc->proc_name.vpid = i;

        if (i == OMPI_PROC_MY_NAME->vpid) {
            ompi_proc_local_proc = proc;
            proc->proc_flags = OPAL_PROC_ALL_LOCAL;
            proc->proc_hostname = ompi_process_info.nodename;
            proc->proc_arch = opal_local_arch;
#if OPAL_ENABLE_HETEROGENEOUS_SUPPORT

            if (OMPI_SUCCESS != (ret = ompi_modex_send_key_value("OMPI_ARCH", &proc->proc_arch, OPAL_UINT32))) {
                return ret;
            }
#endif
        }
    }

    return OMPI_SUCCESS;
}
