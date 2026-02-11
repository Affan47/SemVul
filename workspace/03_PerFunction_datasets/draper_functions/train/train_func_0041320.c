mca_btl_openib_proc_lookup_ompi(ompi_proc_t* ompi_proc)
{
    mca_btl_openib_proc_t* ib_proc;

    OPAL_THREAD_LOCK(&mca_btl_openib_component.ib_lock);

    for(ib_proc = (mca_btl_openib_proc_t*)
            opal_list_get_first(&mca_btl_openib_component.ib_procs);
            ib_proc != (mca_btl_openib_proc_t*)
            opal_list_get_end(&mca_btl_openib_component.ib_procs);
            ib_proc  = (mca_btl_openib_proc_t*)opal_list_get_next(ib_proc)) {
        if(ib_proc->proc_ompi == ompi_proc) {
            OPAL_THREAD_UNLOCK(&mca_btl_openib_component.ib_lock);
            return ib_proc;
        }
    }
    OPAL_THREAD_UNLOCK(&mca_btl_openib_component.ib_lock);
    return NULL;
}
