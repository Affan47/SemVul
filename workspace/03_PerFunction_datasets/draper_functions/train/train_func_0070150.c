compress_gzip_register (void)
{
    int ret;

    mca_compress_gzip_component.super.priority = 15;
    ret = mca_base_component_var_register (&mca_compress_gzip_component.super.base_version,
                                           "priority", "Priority of the COMPRESS gzip component "
                                           "(default: 15)", MCA_BASE_VAR_TYPE_INT, NULL, 0,
                                           MCA_BASE_VAR_FLAG_SETTABLE,
                                           OPAL_INFO_LVL_9, MCA_BASE_VAR_SCOPE_ALL_EQ,
                                           &mca_compress_gzip_component.super.priority);
    if (0 > ret) {
        return ret;
    }

    mca_compress_gzip_component.super.verbose = 0;
    ret = mca_base_component_var_register (&mca_compress_gzip_component.super.base_version,
                                           "verbose",
                                           "Verbose level for the COMPRESS gzip component",
                                           MCA_BASE_VAR_TYPE_INT, NULL, 0, MCA_BASE_VAR_FLAG_SETTABLE,
                                           OPAL_INFO_LVL_9, MCA_BASE_VAR_SCOPE_LOCAL,
                                           &mca_compress_gzip_component.super.verbose);
    return (0 > ret) ? ret : OPAL_SUCCESS;
}
