openib_dereg_mr(void *reg_data, mca_mpool_base_registration_t *reg)
{
    mca_btl_openib_device_t *device = (mca_btl_openib_device_t*)reg_data;
    mca_btl_openib_reg_t *openib_reg = (mca_btl_openib_reg_t*)reg;

    OPAL_OUTPUT_VERBOSE((30, mca_btl_openib_component.memory_registration_verbose,
                         "openib_dereg_mr: base=%p, bound=%p, size=%d, flags=0x%x", reg->base, reg->bound,
                         (int) (reg->bound - reg->base + 1), reg->flags));

    if(openib_reg->mr != NULL) {
        if(ibv_dereg_mr(openib_reg->mr)) {
            BTL_ERROR(("%s: error unpinning openib memory errno says %s",
                       __func__, strerror(errno)));
            return OMPI_ERROR;
        }

#if OPAL_CUDA_SUPPORT
        if (reg->flags & MCA_MPOOL_FLAGS_CUDA_REGISTER_MEM) {
            mca_common_cuda_unregister(openib_reg->base.base,
                openib_reg->base.mpool->mpool_component->mpool_version.mca_component_name);
        }
#endif

    }

    device->mem_reg_active -= (uint64_t) (reg->bound - reg->base + 1);

    openib_reg->mr = NULL;
    return OMPI_SUCCESS;
}
