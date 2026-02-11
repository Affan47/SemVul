usnic_pvar_read(const struct mca_base_pvar_t *pvar,
                           void *value, void *bound_obj)
{
    size_t i;
    size_t offset = (size_t) pvar->ctx;
    uint64_t *array = (uint64_t*) value;

    for (i = 0; i < mca_btl_usnic_component.num_modules; ++i) {
        char *base = (char*) &(mca_btl_usnic_component.usnic_active_modules[i]->stats);
        array[i] = *((uint64_t*) (base + offset));
    }

    return OMPI_SUCCESS;
}
