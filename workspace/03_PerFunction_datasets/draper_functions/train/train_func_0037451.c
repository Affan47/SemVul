mca_coll_basic_alltoall_inter(void *sbuf, int scount,
                              struct ompi_datatype_t *sdtype,
                              void *rbuf, int rcount,
                              struct ompi_datatype_t *rdtype,
                              struct ompi_communicator_t *comm,
                              mca_coll_base_module_t *module)
{
    int i;
    int size;
    int err;
    int nreqs;
    char *psnd;
    char *prcv;
    MPI_Aint lb;
    MPI_Aint sndinc;
    MPI_Aint rcvinc;

    ompi_request_t **req;
    ompi_request_t **sreq;
    ompi_request_t **rreq;

    mca_coll_basic_module_t *basic_module = (mca_coll_basic_module_t*) module;


    size = ompi_comm_remote_size(comm);

    err = ompi_datatype_get_extent(sdtype, &lb, &sndinc);
    if (OMPI_SUCCESS != err) {
        return err;
    }
    sndinc *= scount;

    err = ompi_datatype_get_extent(rdtype, &lb, &rcvinc);
    if (OMPI_SUCCESS != err) {
        return err;
    }
    rcvinc *= rcount;


    nreqs = size * 2;
    req = rreq = basic_module->mccb_reqs;
    sreq = rreq + size;

    prcv = (char *) rbuf;
    psnd = (char *) sbuf;


    for (i = 0; i < size; i++, ++rreq) {
        err = MCA_PML_CALL(irecv(prcv + (i * rcvinc), rcount, rdtype, i,
                                 MCA_COLL_BASE_TAG_ALLTOALL, comm, rreq));
        if (OMPI_SUCCESS != err) {
            return err;
        }
    }


    for (i = 0; i < size; i++, ++sreq) {
        err = MCA_PML_CALL(isend(psnd + (i * sndinc), scount, sdtype, i,
                                 MCA_COLL_BASE_TAG_ALLTOALL,
                                 MCA_PML_BASE_SEND_STANDARD, comm, sreq));
        if (OMPI_SUCCESS != err) {
            return err;
        }
    }


    err = ompi_request_wait_all(nreqs, req, MPI_STATUSES_IGNORE);


    return err;
}
