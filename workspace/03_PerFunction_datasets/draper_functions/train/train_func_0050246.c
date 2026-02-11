mca_spml_yoda_get_request_free(struct oshmem_request_t** request)
{
    mca_spml_yoda_get_request_t* getreq =
            *(mca_spml_yoda_get_request_t**) request;

    assert( false == getreq->req_get.req_base.req_free_called);

    OPAL_THREAD_LOCK(&oshmem_request_lock);
    getreq->req_get.req_base.req_free_called = true;

    OMPI_FREE_LIST_RETURN_MT( &mca_spml_base_get_requests,
                          (ompi_free_list_item_t*)getreq);

    OPAL_THREAD_UNLOCK(&oshmem_request_lock);

    *request = SHMEM_REQUEST_NULL;
    return OSHMEM_SUCCESS;
}
