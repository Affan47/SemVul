mca_coll_basic_alltoallv_inter(void *sbuf, int *scounts, int *sdisps,
                               struct ompi_datatype_t *sdtype, void *rbuf,
                               int *rcounts, int *rdisps,
                               struct ompi_datatype_t *rdtype,
                               struct ompi_communicator_t *comm,
                               mca_coll_base_module_t *module)
{
    int i;
    int rsize;
    int err;
    char *psnd;
    char *prcv;
    size_t nreqs;
    MPI_Aint sndextent;
    MPI_Aint rcvextent;

    mca_coll_basic_module_t *basic_module = (mca_coll_basic_module_t*) module;
    ompi_request_t **preq = basic_module->mccb_reqs;


    rsize = ompi_comm_remote_size(comm);

    ompi_datatype_type_extent(sdtype, &sndextent);
    ompi_datatype_type_extent(rdtype, &rcvextent);


    nreqs = rsize * 2;


    for (i = 0; i < rsize; ++i) {
        prcv = ((char *) rbuf) + (rdisps[i] * rcvextent);
        if (rcounts[i] > 0) {
            err = MCA_PML_CALL(irecv(prcv, rcounts[i], rdtype,
                                     i, MCA_COLL_BASE_TAG_ALLTOALLV, comm,
                                     &preq[i]));
            if (MPI_SUCCESS != err) {
                return err;
            }
        } else {
            preq[i] = MPI_REQUEST_NULL;
        }
    }


    for (i = 0; i < rsize; ++i) {
        psnd = ((char *) sbuf) + (sdisps[i] * sndextent);
        if (scounts[i] > 0) {
            err = MCA_PML_CALL(isend(psnd, scounts[i], sdtype,
                                     i, MCA_COLL_BASE_TAG_ALLTOALLV,
                                     MCA_PML_BASE_SEND_STANDARD, comm,
                                     &preq[rsize + i]));
            if (MPI_SUCCESS != err) {
                return err;
            }
        } else {
            preq[rsize + i] = MPI_REQUEST_NULL;
        }
    }

    err = ompi_request_wait_all(nreqs, preq, MPI_STATUSES_IGNORE);


    return err;
}
