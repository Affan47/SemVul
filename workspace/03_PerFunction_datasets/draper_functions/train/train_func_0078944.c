ompi_osc_rdma_callback (ompi_request_t *request)
{
    ompi_osc_rdma_module_t *module = (ompi_osc_rdma_module_t *) request->req_complete_cb_data;
    ompi_osc_rdma_header_base_t *base_header =
        (ompi_osc_rdma_header_base_t *) module->incoming_buffer;
    size_t incoming_length = request->req_status._ucount;
    int source = request->req_status.MPI_SOURCE;

    OPAL_THREAD_UNLOCK(&ompi_request_lock);

    assert(incoming_length >= sizeof(ompi_osc_rdma_header_base_t));

    OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                         "received rdma callback for fragment. source = %d, count = %u, type = 0x%x",
                         source, (unsigned) incoming_length, base_header->type));

    switch (base_header->type) {
    case OMPI_OSC_RDMA_HDR_TYPE_FRAG:
        process_frag(module, (ompi_osc_rdma_frag_header_t *) base_header);
        break;
    case OMPI_OSC_RDMA_HDR_TYPE_POST:
        (void) osc_rdma_incoming_post (module);
        break;
    case OMPI_OSC_RDMA_HDR_TYPE_LOCK_ACK:
        ompi_osc_rdma_process_lock_ack(module, (ompi_osc_rdma_header_lock_ack_t *) base_header);
        break;
    case OMPI_OSC_RDMA_HDR_TYPE_FLUSH_ACK:
        ompi_osc_rdma_process_flush_ack (module, source, (ompi_osc_rdma_header_flush_ack_t *) base_header);
        break;
    case OMPI_OSC_RDMA_HDR_TYPE_UNLOCK_ACK:
        ompi_osc_rdma_process_unlock_ack (module, source, (ompi_osc_rdma_header_unlock_ack_t *) base_header);
        break;
    default:
        OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                             "received unexpected message of type %x",
                             (int) base_header->type));
    }

    OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                         "finished processing incoming messages"));


    OPAL_THREAD_LOCK(&module->lock);

    mark_incoming_completion (module, (base_header->flags & OMPI_OSC_RDMA_HDR_FLAG_PASSIVE_TARGET) ?
                              source : MPI_PROC_NULL);

    osc_rdma_gc_clean ();


    osc_rdma_gc_add_request (request);
    ompi_osc_rdma_frag_start_receive (module);

    OPAL_THREAD_UNLOCK(&module->lock);

    OPAL_THREAD_LOCK(&ompi_request_lock);

    OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                         "finished posting receive request"));

    return OMPI_SUCCESS;
}
