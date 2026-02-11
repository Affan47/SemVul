reg_string(const char* param_name,
                      const char* help_string,
                      const char* default_value, char **storage,
                      int flags, int level)
{
    *storage = (char*) default_value;
    mca_base_component_var_register(&mca_btl_usnic_component.super.btl_version,
                                    param_name, help_string,
                                    MCA_BASE_VAR_TYPE_STRING,
                                    NULL,
                                    0,
                                    0,
                                    level,
                                    MCA_BASE_VAR_SCOPE_READONLY,
                                    storage);

    if (0 == (flags & REGSTR_EMPTY_OK) &&
        (NULL == *storage || 0 == strlen(*storage))) {
        opal_output(0, "Bad parameter value for parameter \"%s\"",
                    param_name);
        return OMPI_ERR_BAD_PARAM;
    }

    return OMPI_SUCCESS;
}
