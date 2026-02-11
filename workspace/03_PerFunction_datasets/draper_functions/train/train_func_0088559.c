mca_vprotocol_pessimist_test_all(size_t count, ompi_request_t ** requests,
                                     int *completed,
                                     ompi_status_public_t * statuses)
{
    int ret;
    int index;


    VPROTOCOL_PESSIMIST_DELIVERY_REPLAY(1, requests, completed, &index, statuses);

    ret = mca_pml_v.host_request_fns.req_test_all(count, requests, completed,
                                                   statuses);
#if 0

    if(completed)
        vprotocol_pessimist_delivery_log(requests);
    else
        vprotocol_pessimist_delivery_log(NULL);
#endif
    return ret;
}
