device_construct(mca_btl_openib_device_t *device)
{
    device->ib_dev = NULL;
    device->ib_dev_context = NULL;
    device->ib_pd = NULL;
    device->mpool = NULL;
#if OMPI_ENABLE_PROGRESS_THREADS
    device->ib_channel = NULL;
#endif
    device->btls = 0;
    device->endpoints = NULL;
    device->device_btls = NULL;
    device->ib_cq[BTL_OPENIB_HP_CQ] = NULL;
    device->ib_cq[BTL_OPENIB_LP_CQ] = NULL;
    device->cq_size[BTL_OPENIB_HP_CQ] = 0;
    device->cq_size[BTL_OPENIB_LP_CQ] = 0;
    device->non_eager_rdma_endpoints = 0;
    device->hp_cq_polls = mca_btl_openib_component.cq_poll_ratio;
    device->eager_rdma_polls = mca_btl_openib_component.eager_rdma_poll_ratio;
    device->pollme = true;
    device->eager_rdma_buffers_count = 0;
    device->eager_rdma_buffers = NULL;
#if HAVE_XRC
    device->xrc_fd = -1;
#endif
    device->qps = NULL;
#if OPAL_HAVE_THREADS
    mca_btl_openib_component.async_pipe[0] =
        mca_btl_openib_component.async_pipe[1] = -1;
    mca_btl_openib_component.async_comp_pipe[0] =
        mca_btl_openib_component.async_comp_pipe[1] = -1;
#endif
    OBJ_CONSTRUCT(&device->device_lock, opal_mutex_t);
    OBJ_CONSTRUCT(&device->send_free_control, ompi_free_list_t);
    device->max_inline_data = 0;
}
