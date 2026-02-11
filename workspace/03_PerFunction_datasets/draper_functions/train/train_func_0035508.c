ompi_coll_tuned_reduce_scatter_intra_nonoverlapping(void *sbuf, void *rbuf,
                                                        int *rcounts,
                                                        struct ompi_datatype_t *dtype,
                                                        struct ompi_op_t *op,
                                                        struct ompi_communicator_t *comm,
                                                        mca_coll_base_module_t *module)
{
    int err, i, rank, size, total_count, *displs = NULL;
    const int root = 0;
    char *tmprbuf = NULL, *tmprbuf_free = NULL;

    rank = ompi_comm_rank(comm);
    size = ompi_comm_size(comm);

    OPAL_OUTPUT((ompi_coll_tuned_stream,"coll:tuned:reduce_scatter_intra_nonoverlapping, rank %d", rank));

    for (i = 0, total_count = 0; i < size; i++) { total_count += rcounts[i]; }


    tmprbuf = (char*) rbuf;
    if (MPI_IN_PLACE == sbuf) {

        if (root == rank) {
            err = comm->c_coll.coll_reduce (MPI_IN_PLACE, tmprbuf, total_count,
                                            dtype, op, root, comm, comm->c_coll.coll_reduce_module);
        } else {
            err = comm->c_coll.coll_reduce(tmprbuf, NULL, total_count,
                                           dtype, op, root, comm, comm->c_coll.coll_reduce_module);
        }
    } else {
        if (root == rank) {


            ptrdiff_t lb, extent, tlb, textent;

            ompi_datatype_get_extent(dtype, &lb, &extent);
            ompi_datatype_get_true_extent(dtype, &tlb, &textent);

            tmprbuf_free = (char*) malloc(textent + (ptrdiff_t)(total_count - 1) * extent);
            tmprbuf = tmprbuf_free - lb;
        }
        err = comm->c_coll.coll_reduce (sbuf, tmprbuf, total_count,
                                        dtype, op, root, comm, comm->c_coll.coll_reduce_module);
    }
    if (MPI_SUCCESS != err) {
        if (NULL != tmprbuf_free) free(tmprbuf_free);
        return err;
    }

    displs = (int*) malloc(size * sizeof(int));
    displs[0] = 0;
    for (i = 1; i < size; i++) {
        displs[i] = displs[i-1] + rcounts[i-1];
    }
    err =  comm->c_coll.coll_scatterv (tmprbuf, rcounts, displs, dtype,
                                       rbuf, rcounts[rank], dtype,
                                       root, comm, comm->c_coll.coll_scatterv_module);
    free(displs);
    if (NULL != tmprbuf_free) free(tmprbuf_free);

    return err;
}
