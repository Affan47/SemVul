bcol_ptpcoll_allreduce_narray_schedule_extra_node_exchange (mca_bcol_ptpcoll_module_t *ptpcoll_module, netpatterns_k_exchange_node_t *k_node,
                                                                              void *data_buffer, size_t data_size, ompi_request_t **requests, int *active_requests,
                                                                              int tag)
{
    ompi_communicator_t *comm = ptpcoll_module->super.sbgp_partner_module->group_comm;
    int peer_comm_rank, k, offset, rc;

    if (EXCHANGE_NODE == k_node->node_type) {

        for (k = 0, offset = data_size ; k < k_node->n_extra_sources ; ++k, offset += data_size) {
            peer_comm_rank = ptpcoll_module->super.sbgp_partner_module->group_list[k_node->rank_extra_sources_array[k]];

            PTPCOLL_VERBOSE(10, ("Recv data from %d, addr %p len %d tag %d",
                                 peer_comm_rank, data_buffer, data_size, tag));
            rc = MCA_PML_CALL(irecv((void *)((unsigned char *)data_buffer + offset),
                                    data_size, MPI_BYTE, peer_comm_rank, tag, comm,
                                    &requests[*active_requests]));
            if( OMPI_SUCCESS != rc ) {
                PTPCOLL_VERBOSE(10, ("Failed to receive data"));
                return OMPI_ERROR;
            }

            ++(*active_requests);
        }
    } else {
        peer_comm_rank = ptpcoll_module->super.sbgp_partner_module->group_list[k_node->rank_extra_sources_array[0]];

        PTPCOLL_VERBOSE(10, ("Send data to %d, addr %p len %d tag %d",
                             peer_comm_rank, data_buffer, data_size, tag));

        rc = MCA_PML_CALL(isend(data_buffer, data_size, MPI_BYTE, peer_comm_rank,
                                tag, MCA_PML_BASE_SEND_STANDARD, comm,
                                &(requests[*active_requests])));
        if( OMPI_SUCCESS != rc ) {
            PTPCOLL_VERBOSE(10, ("Failed to send data"));
            return OMPI_ERROR;
        }

        ++(*active_requests);
    }

    return OMPI_SUCCESS;
}
