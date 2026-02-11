mca_pml_bfo_irecv(void *addr,
                      size_t count,
                      ompi_datatype_t * datatype,
                      int src,
                      int tag,
                      struct ompi_communicator_t *comm,
                      struct ompi_request_t **request)
{
    mca_pml_bfo_recv_request_t *recvreq;
    MCA_PML_BFO_RECV_REQUEST_ALLOC(recvreq);
    if (NULL == recvreq)
        return OMPI_ERR_OUT_OF_RESOURCE;

    MCA_PML_BFO_RECV_REQUEST_INIT(recvreq,
                                   addr,
                                   count, datatype, src, tag, comm, false);

    PERUSE_TRACE_COMM_EVENT (PERUSE_COMM_REQ_ACTIVATE,
                             &((recvreq)->req_recv.req_base),
                             PERUSE_RECV);

    MCA_PML_BFO_RECV_REQUEST_START(recvreq);
    *request = (ompi_request_t *) recvreq;
    return OMPI_SUCCESS;
}
