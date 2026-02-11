opal_dss_register_vars (void)
{
    mca_base_var_enum_t *new_enum;
    char *enviro_val;
    int ret;

    enviro_val = getenv("OPAL_dss_debug");
    if (NULL != enviro_val) {
        opal_dss_verbose = 0;
    }

    opal_dss_group_id = mca_base_var_group_register ("opal", "dss", NULL, NULL);


#if OPAL_ENABLE_DEBUG
    default_buf_type = OPAL_DSS_BUFFER_FULLY_DESC;
#else
    default_buf_type = OPAL_DSS_BUFFER_NON_DESC;
#endif

    ret = mca_base_var_enum_create ("buffer types", buffer_type_values, &new_enum);
    if (OPAL_SUCCESS != ret) {
        fprintf (stderr, "Fail A\n");
        return ret;
    }

    ret = mca_base_var_register ("opal", "dss", NULL, "buffer_type",
                                 "Set the default mode for OpenRTE buffers (0=non-described, 1=described)",
                                 MCA_BASE_VAR_TYPE_INT, new_enum, 0, MCA_BASE_VAR_FLAG_SETTABLE,
                                 OPAL_INFO_LVL_8, MCA_BASE_VAR_SCOPE_ALL_EQ,
                                 &default_buf_type);
    OBJ_RELEASE(new_enum);
    if (0 > ret) {
        return ret;
    }


    opal_dss_initial_size = OPAL_DSS_DEFAULT_INITIAL_SIZE;
    ret = mca_base_var_register ("opal", "dss", NULL, "buffer_initial_size", NULL,
                                 MCA_BASE_VAR_TYPE_INT, NULL, 0, MCA_BASE_VAR_FLAG_SETTABLE,
                                 OPAL_INFO_LVL_8, MCA_BASE_VAR_SCOPE_ALL_EQ,
                                 &opal_dss_initial_size);
    if (0 > ret) {
        return ret;
    }


    opal_dss_threshold_size = OPAL_DSS_DEFAULT_THRESHOLD_SIZE;
    ret = mca_base_var_register ("opal", "dss", NULL, "buffer_threshold_size", NULL,
                                 MCA_BASE_VAR_TYPE_INT, NULL, 0, MCA_BASE_VAR_FLAG_SETTABLE,
                                 OPAL_INFO_LVL_8, MCA_BASE_VAR_SCOPE_ALL_EQ,
                                 &opal_dss_threshold_size);

    return (0 > ret) ? ret : OPAL_SUCCESS;
}
