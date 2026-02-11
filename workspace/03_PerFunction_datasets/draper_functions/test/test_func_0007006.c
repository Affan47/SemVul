libnbc_open(void)
{
    int ret;

    OBJ_CONSTRUCT(&mca_coll_libnbc_component.requests, ompi_free_list_t);
    ret = ompi_free_list_init(&mca_coll_libnbc_component.requests,
                              sizeof(ompi_coll_libnbc_request_t),
                              OBJ_CLASS(ompi_coll_libnbc_request_t),
                              0,
                              -1,
                              8,
                              NULL);
    if (OMPI_SUCCESS != ret) return ret;

    OBJ_CONSTRUCT(&mca_coll_libnbc_component.active_requests, opal_list_t);


    mca_coll_libnbc_component.active_comms = 0;

    opal_atomic_init(&mca_coll_libnbc_component.progress_lock, OPAL_ATOMIC_UNLOCKED);

    return OMPI_SUCCESS;
}
