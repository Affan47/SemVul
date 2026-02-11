mca_bcol_ptpcoll_comm_query(mca_sbgp_base_module_t *sbgp,
                                                     int *num_modules)
{
    int rc;

    struct ompi_communicator_t *comm = sbgp->group_comm;
    mca_bcol_ptpcoll_module_t *ptpcoll_module = NULL;
    mca_bcol_base_module_t **ptpcoll_modules = NULL;
    int iovec_size;


    *num_modules = 0;


    if (OMPI_COMM_IS_INTER(comm) ) {
        return NULL;
    }


    ptpcoll_modules = (mca_bcol_base_module_t **) malloc(sizeof(mca_bcol_base_module_t *));
    if (NULL == ptpcoll_modules) {
        return NULL;
    }

    ptpcoll_module = OBJ_NEW(mca_bcol_ptpcoll_module_t);
    if (NULL == ptpcoll_module) {
        return NULL;
    }


    ptpcoll_modules[*num_modules] = &(ptpcoll_module->super);

    (*num_modules)++;

    ptpcoll_module->super.sbgp_partner_module = sbgp;

    ptpcoll_module->group_size =
        ptpcoll_module->super.sbgp_partner_module->group_size;

    rc = load_binomial_info(ptpcoll_module);
    if (OMPI_SUCCESS != rc) {
        PTPCOLL_VERBOSE(10, ("Failed to load knomial info"));
        goto CLEANUP;
    }

    rc = load_knomial_info(ptpcoll_module);
    if (OMPI_SUCCESS != rc) {
        PTPCOLL_VERBOSE(10, ("Failed to load knomial info"));
        goto CLEANUP;
    }

    rc = load_narray_tree(ptpcoll_module);
    if (OMPI_SUCCESS != rc) {
        PTPCOLL_VERBOSE(10, ("Failed to load narray tree"));
        goto CLEANUP;
    }

    rc = load_narray_knomial_tree(ptpcoll_module);
    if (OMPI_SUCCESS != rc) {
        PTPCOLL_VERBOSE(10, ("Failed to load narray-knomila tree"));
        goto CLEANUP;
    }

    rc = load_recursive_knomial_info(ptpcoll_module);
    if (OMPI_SUCCESS != rc) {
        PTPCOLL_VERBOSE(10, ("Failed to load recursive knomial tree"));
        goto CLEANUP;
    }


    OBJ_CONSTRUCT(&ptpcoll_module->collreqs_free, ompi_free_list_t);
    rc = ompi_free_list_init_ex_new(&ptpcoll_module->collreqs_free,
                                    sizeof(mca_bcol_ptpcoll_collreq_t),
                                    BCOL_PTP_CACHE_LINE_SIZE,
                                    OBJ_CLASS(mca_bcol_ptpcoll_collreq_t),
                                    0, BCOL_PTP_CACHE_LINE_SIZE,
                                    256 ,
                                    -1  ,
                                    32  ,
                                    NULL,
                                    bcol_ptpcoll_collreq_init,
                                    ptpcoll_module);
    if (OMPI_SUCCESS != rc) {
        goto CLEANUP;
    }

    load_func(ptpcoll_module);

    rc = alloc_allreduce_offsets_array(ptpcoll_module);
    if (OMPI_SUCCESS != rc) {
        goto CLEANUP;
    }


    iovec_size = ptpcoll_module->group_size / 2 + ptpcoll_module->group_size % 2;
    ptpcoll_module->alltoall_iovec = (struct iovec *) malloc(sizeof(struct iovec)
                                                             * iovec_size);
    ptpcoll_module->log_group_size = lognum(ptpcoll_module->group_size);

    rc = mca_bcol_base_bcol_fns_table_init(&(ptpcoll_module->super));
    if (OMPI_SUCCESS != rc) {
        goto CLEANUP;
    }


    ptpcoll_module->super.supported_mode = MCA_BCOL_BASE_ZERO_COPY;


    return ptpcoll_modules;

CLEANUP:

    OBJ_RELEASE(ptpcoll_module);
    return NULL;
}
