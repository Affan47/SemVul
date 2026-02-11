oshmem_group_cache_list_init(void)
{
    int mca_value;
    int cache_size_default = 100;
    OBJ_CONSTRUCT(&oshmem_group_cache_list, opal_list_t);

    mca_value = cache_size_default;
    (void) mca_base_var_register("oshmem",
                                 "proc",
                                 NULL,
                                 "group_cache_size",
                                 "The depth of the oshmem_group cache list used to speed up collective operations",
                                 MCA_BASE_VAR_TYPE_INT,
                                 NULL,
                                 0,
                                 MCA_BASE_VAR_FLAG_SETTABLE,
                                 OPAL_INFO_LVL_9,
                                 MCA_BASE_VAR_SCOPE_READONLY,
                                 &mca_value);
    if (mca_value < 0) {
        opal_output(0,
                    "error: oshmem_group_cache_size mca parameter was set to %i while it has to be positive value. Default value %i will be used.",
                    mca_value,
                    cache_size_default);
        mca_value = cache_size_default;
    }
    oshmem_group_cache_size = (unsigned int) mca_value;
    return OSHMEM_SUCCESS;
}
