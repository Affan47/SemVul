btl_openib_verify_mca_params (void)
{
    if (mca_btl_openib_component.cq_poll_batch > MCA_BTL_OPENIB_CQ_POLL_BATCH_DEFAULT) {
        mca_btl_openib_component.cq_poll_batch = MCA_BTL_OPENIB_CQ_POLL_BATCH_DEFAULT;
    }

#if !HAVE_IBV_FORK_INIT
    if (0 != mca_btl_openib_component.want_fork_support) {
        opal_show_help("help-mpi-btl-openib.txt",
                       "ibv_fork requested but not supported", true,
                       ompi_process_info.nodename);
        return OMPI_ERR_BAD_PARAM;
    }
#endif

    mca_btl_openib_component.ib_pkey_val &= MCA_BTL_IB_PKEY_MASK;

    if (mca_btl_openib_component.ib_min_rnr_timer > 31) {
        opal_show_help("help-mpi-btl-openib.txt", "invalid mca param value",
                       true, "btl_openib_ib_min_rnr_timer > 31",
                       "btl_openib_ib_min_rnr_timer reset to 31");
        mca_btl_openib_component.ib_min_rnr_timer = 31;
    }

    if (mca_btl_openib_component.ib_timeout > 31) {
        opal_show_help("help-mpi-btl-openib.txt", "invalid mca param value",
                       true, "btl_openib_ib_timeout > 31",
                       "btl_openib_ib_timeout reset to 31");
        mca_btl_openib_component.ib_timeout = 31;
    }

    if (mca_btl_openib_component.ib_retry_count > 7) {
        opal_show_help("help-mpi-btl-openib.txt", "invalid mca param value",
                       true, "btl_openib_ib_retry_count > 7",
                       "btl_openib_ib_retry_count reset to 7");
        mca_btl_openib_component.ib_retry_count = 7;
    }

    if (mca_btl_openib_component.ib_rnr_retry > 7) {
        opal_show_help("help-mpi-btl-openib.txt", "invalid mca param value",
                       true, "btl_openib_ib_rnr_retry > 7",
                       "btl_openib_ib_rnr_retry reset to 7");
        mca_btl_openib_component.ib_rnr_retry = 7;
    }

    if (mca_btl_openib_component.ib_service_level > 15) {
        opal_show_help("help-mpi-btl-openib.txt", "invalid mca param value",
                       true, "btl_openib_ib_service_level > 15",
                       "btl_openib_ib_service_level reset to 15");
        mca_btl_openib_component.ib_service_level = 15;
    }

    if(mca_btl_openib_component.buffer_alignment <= 1 ||
       (mca_btl_openib_component.buffer_alignment & (mca_btl_openib_component.buffer_alignment - 1))) {
        opal_show_help("help-mpi-btl-openib.txt", "wrong buffer alignment",
                true, mca_btl_openib_component.buffer_alignment, ompi_process_info.nodename, 64);
        mca_btl_openib_component.buffer_alignment = 64;
    }

#if OPAL_CUDA_SUPPORT
    if (mca_btl_openib_component.cuda_async_send) {
        mca_btl_openib_module.super.btl_flags |= MCA_BTL_FLAGS_CUDA_COPY_ASYNC_SEND;
    } else {
        mca_btl_openib_module.super.btl_flags &= ~MCA_BTL_FLAGS_CUDA_COPY_ASYNC_SEND;
    }

    if (mca_btl_openib_component.cuda_async_recv) {
        mca_btl_openib_module.super.btl_flags |= MCA_BTL_FLAGS_CUDA_COPY_ASYNC_RECV;
    } else {
        mca_btl_openib_module.super.btl_flags &= ~MCA_BTL_FLAGS_CUDA_COPY_ASYNC_RECV;
    }
#endif

#if BTL_OPENIB_MALLOC_HOOKS_ENABLED
    if (mca_btl_openib_component.use_memalign != 32
        && mca_btl_openib_component.use_memalign != 64
        && mca_btl_openib_component.use_memalign != 0){
        opal_show_help("help-mpi-btl-openib.txt", "invalid mca param value",
                       true, "Wrong btl_openib_memalign parameter value. Allowed values: 64, 32, 0.",
                       "btl_openib_memalign is reset to 32");
        mca_btl_openib_component.use_memalign = 32;
    }
#endif

    return OMPI_SUCCESS;
}
