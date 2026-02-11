ompi_coll_tuned_dump_msg_rule (ompi_coll_msg_rule_t* msg_p)
{
    if (!msg_p) {
        OPAL_OUTPUT((ompi_coll_tuned_stream,"Message rule was a NULL ptr?!\n"));
        return (-1);
    }

    OPAL_OUTPUT((ompi_coll_tuned_stream,"alg_id %3d\tcom_id %3d\tcom_size %3d\tmsg_id %3d\t", msg_p->alg_rule_id,
                 msg_p->com_rule_id, msg_p->mpi_comsize, msg_p->msg_rule_id));

    OPAL_OUTPUT((ompi_coll_tuned_stream,"msg_size %10lu -> algorithm %2d\ttopo in/out %2d\tsegsize %5ld\tmax_requests %4d\n",
                 msg_p->msg_size, msg_p->result_alg, msg_p->result_topo_faninout, msg_p->result_segsize,
                 msg_p->result_max_requests));

    return (0);
}
