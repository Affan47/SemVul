reg_bool(const char* param_name,
                    const char* deprecated_param_name,
                    const char* param_desc,
                    bool default_value, bool *storage)
{
    int index;

    *storage = default_value;
    index = mca_base_component_var_register(&mca_bcol_ptpcoll_component.super.bcol_version,
                                            param_name, param_desc, MCA_BASE_VAR_TYPE_BOOL,
                                            NULL, 0, 0, OPAL_INFO_LVL_9,
                                            MCA_BASE_VAR_SCOPE_READONLY, storage);
    if (0 > index) {
        return index;
    }

    if (NULL != deprecated_param_name) {
        (void) mca_base_var_register_synonym(index, "ompi", "bcol", "ptpcoll",
                                             deprecated_param_name,
                                             MCA_BASE_VAR_SYN_FLAG_DEPRECATED);
    }

    return OMPI_SUCCESS;
}
