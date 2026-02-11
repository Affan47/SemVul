activate_lock (ompi_osc_rdma_module_t *module, int requestor,
                                 uint64_t serial_number)
{
    ompi_osc_rdma_outstanding_lock_t *lock;

    if (ompi_comm_rank (module->comm) != requestor) {
        ompi_osc_rdma_header_lock_ack_t lock_ack;

        lock_ack.base.type = OMPI_OSC_RDMA_HDR_TYPE_LOCK_ACK;
        lock_ack.base.flags = OMPI_OSC_RDMA_HDR_FLAG_VALID;
        lock_ack.source = ompi_comm_rank(module->comm);
        lock_ack.windx = ompi_comm_get_cid(module->comm);
        lock_ack.serial_number = serial_number;

        OPAL_OUTPUT_VERBOSE((25, ompi_osc_base_framework.framework_output,
                             "osc rdma: sending lock to %d", requestor));


        return ompi_osc_rdma_control_send_unbuffered (module, requestor, &lock_ack, sizeof (lock_ack));
    }


    OPAL_OUTPUT_VERBOSE((25, ompi_osc_base_framework.framework_output,
                         "osc rdma: releasing local lock"));

    lock = find_outstanding_lock (module, requestor);
    if (NULL == lock) {
        lock = find_outstanding_lock (module, -1);
        if (OPAL_UNLIKELY(NULL == lock)) {
            OPAL_OUTPUT_VERBOSE((5, ompi_osc_base_framework.framework_output,
                                 "lock could not be located"));
        }
    }

    lock->lock_acks_received++;
    opal_condition_broadcast (&module->cond);

    return OMPI_SUCCESS;
}
