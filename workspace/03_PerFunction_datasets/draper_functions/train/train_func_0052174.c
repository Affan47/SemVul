ompi_coll_tuned_barrier_intra_recursivedoubling(struct ompi_communicator_t *comm,
                                                    mca_coll_base_module_t *module)
{
    int rank, size, adjsize, err, line, mask, remote;

    rank = ompi_comm_rank(comm);
    size = ompi_comm_size(comm);
    OPAL_OUTPUT((ompi_coll_tuned_stream,
                 "ompi_coll_tuned_barrier_intra_recursivedoubling rank %d",
                 rank));


    adjsize = opal_next_poweroftwo(size);
    adjsize >>= 1;


    if (adjsize != size) {
        if (rank >= adjsize) {

            remote = rank - adjsize;
            err = ompi_coll_tuned_sendrecv_actual(NULL, 0, MPI_BYTE, remote,
                                                  MCA_COLL_BASE_TAG_BARRIER,
                                                  NULL, 0, MPI_BYTE, remote,
                                                  MCA_COLL_BASE_TAG_BARRIER,
                                                  comm, MPI_STATUS_IGNORE);
            if (err != MPI_SUCCESS) { line = __LINE__; goto err_hndl;}

        } else if (rank < (size - adjsize)) {


            err = MCA_PML_CALL(recv((void*)NULL, 0, MPI_BYTE, rank+adjsize,
                                    MCA_COLL_BASE_TAG_BARRIER, comm,
                                    MPI_STATUS_IGNORE));

            if (err != MPI_SUCCESS) { line = __LINE__; goto err_hndl;}
        }
    }


    if ( rank < adjsize ) {
        mask = 0x1;
        while ( mask < adjsize ) {
            remote = rank ^ mask;
            mask <<= 1;
            if (remote >= adjsize) continue;


            err = ompi_coll_tuned_sendrecv_actual(NULL, 0, MPI_BYTE, remote,
                                                  MCA_COLL_BASE_TAG_BARRIER,
                                                  NULL, 0, MPI_BYTE, remote,
                                                  MCA_COLL_BASE_TAG_BARRIER,
                                                  comm, MPI_STATUS_IGNORE);
            if (err != MPI_SUCCESS) { line = __LINE__; goto err_hndl;}
        }
    }


    if (adjsize != size) {
        if (rank < (size - adjsize)) {

            remote = rank + adjsize;
            err = MCA_PML_CALL(send((void*)NULL, 0, MPI_BYTE, remote,
                                    MCA_COLL_BASE_TAG_BARRIER,
                                    MCA_PML_BASE_SEND_SYNCHRONOUS, comm));

            if (err != MPI_SUCCESS) { line = __LINE__; goto err_hndl;}
        }
    }

    return MPI_SUCCESS;

 err_hndl:
    OPAL_OUTPUT((ompi_coll_tuned_stream,"%s:%4d\tError occurred %d, rank %2d",
                 __FILE__, line, err, rank));
    return err;
}
