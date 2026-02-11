ompi_coll_tuned_allreduce_intra_do_forced(void *sbuf, void *rbuf, int count,
                                              struct ompi_datatype_t *dtype,
                                              struct ompi_op_t *op,
                                              struct ompi_communicator_t *comm,
                                              mca_coll_base_module_t *module)
{
    mca_coll_tuned_module_t *tuned_module = (mca_coll_tuned_module_t*) module;
    mca_coll_tuned_comm_t *data = tuned_module->tuned_data;

    OPAL_OUTPUT((ompi_coll_tuned_stream,"coll:tuned:allreduce_intra_do_forced selected algorithm %d, segment size %d",
                 data->user_forced[ALLREDUCE].algorithm,
                 data->user_forced[ALLREDUCE].segsize));

    switch (data->user_forced[ALLREDUCE].algorithm) {
    case (0):  return ompi_coll_tuned_allreduce_intra_dec_fixed (sbuf, rbuf, count, dtype, op, comm, module);
    case (1):  return ompi_coll_tuned_allreduce_intra_basic_linear (sbuf, rbuf, count, dtype, op, comm, module);
    case (2):  return ompi_coll_tuned_allreduce_intra_nonoverlapping (sbuf, rbuf, count, dtype, op, comm, module);
    case (3):  return ompi_coll_tuned_allreduce_intra_recursivedoubling (sbuf, rbuf, count, dtype, op, comm, module);
    case (4):  return ompi_coll_tuned_allreduce_intra_ring (sbuf, rbuf, count, dtype, op, comm, module);
    case (5):  return ompi_coll_tuned_allreduce_intra_ring_segmented (sbuf, rbuf, count, dtype, op, comm, module, data->user_forced[ALLREDUCE].segsize);
    default:
        OPAL_OUTPUT((ompi_coll_tuned_stream,"coll:tuned:allreduce_intra_do_forced attempt to select algorithm %d when only 0-%d is valid?",
                     data->user_forced[ALLREDUCE].algorithm,
                     ompi_coll_tuned_forced_max_algorithms[ALLREDUCE]));
        return (MPI_ERR_ARG);
    }

}
