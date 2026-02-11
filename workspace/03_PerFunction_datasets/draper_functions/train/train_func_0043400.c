mca_pml_base_bsend_request_alloc(ompi_request_t* request)
{
    mca_pml_base_send_request_t* sendreq = (mca_pml_base_send_request_t*)request;

    assert( sendreq->req_bytes_packed > 0 );


    OPAL_THREAD_LOCK(&mca_pml_bsend_mutex);
    if(NULL == mca_pml_bsend_addr) {
        sendreq->req_addr = NULL;
        OPAL_THREAD_UNLOCK(&mca_pml_bsend_mutex);
        return OMPI_ERR_BUFFER;
    }


    sendreq->req_addr = mca_pml_bsend_allocator->alc_alloc(
        mca_pml_bsend_allocator, sendreq->req_bytes_packed, 0, NULL);
    if(NULL == sendreq->req_addr) {

        sendreq->req_base.req_pml_complete = true;
        OPAL_THREAD_UNLOCK(&mca_pml_bsend_mutex);


        opal_progress();
        return OMPI_ERR_BUFFER;
    }


    mca_pml_bsend_count++;
    OPAL_THREAD_UNLOCK(&mca_pml_bsend_mutex);

    return OMPI_SUCCESS;
}
