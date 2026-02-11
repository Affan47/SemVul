ompi_comm_determine_first ( ompi_communicator_t *intercomm, int high )
{
    int flag, rhigh;
    int rank, rsize;
    int *rcounts;
    int *rdisps;
    int scount=0;
    int rc;
    ompi_proc_t *ourproc, *theirproc;
    ompi_rte_cmp_bitmask_t mask;

    rank = ompi_comm_rank        (intercomm);
    rsize= ompi_comm_remote_size (intercomm);

    rdisps  = (int *) calloc ( rsize, sizeof(int));
    rcounts = (int *) calloc ( rsize, sizeof(int));
    if ( NULL == rdisps || NULL == rcounts ){
        return OMPI_ERR_OUT_OF_RESOURCE;
    }

    rcounts[0] = 1;
    if ( 0 == rank ) {
        scount = 1;
    }

    rc = intercomm->c_coll.coll_allgatherv(&high, scount, MPI_INT,
                                           &rhigh, rcounts, rdisps,
                                           MPI_INT, intercomm,
                                           intercomm->c_coll.coll_allgatherv_module);
    if ( rc != OMPI_SUCCESS ) {
        flag = MPI_UNDEFINED;
    }

    if ( NULL != rdisps ) {
        free ( rdisps );
    }
    if ( NULL != rcounts ) {
        free ( rcounts );
    }


    if ( high && !rhigh ) {
        flag = false;
    }
    else if ( !high && rhigh ) {
        flag = true;
    }
    else {
        ourproc   = ompi_group_peer_lookup(intercomm->c_local_group,0);
        theirproc = ompi_group_peer_lookup(intercomm->c_remote_group,0);

        mask = OMPI_RTE_CMP_JOBID | OMPI_RTE_CMP_VPID;
        rc = ompi_rte_compare_name_fields(mask, &(ourproc->proc_name), &(theirproc->proc_name));
        if ( 0 > rc ) {
            flag = true;
        }
        else {
            flag = false;
        }
    }

    return flag;
}
