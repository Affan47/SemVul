vader_del_procs(struct mca_btl_base_module_t *btl,
                           size_t nprocs, struct ompi_proc_t **procs,
                           struct mca_btl_base_endpoint_t **peers)
{
    for (size_t i = 0 ; i < nprocs ; ++i) {
        fini_vader_endpoint (peers[i]);
        peers[i] = NULL;
    }

    return OMPI_SUCCESS;
}
