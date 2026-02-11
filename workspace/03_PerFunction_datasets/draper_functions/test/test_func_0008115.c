mca_base_var_check_exclusive (const char *project,
                                  const char *type_a,
                                  const char *component_a,
                                  const char *param_a,
                                  const char *type_b,
                                  const char *component_b,
                                  const char *param_b)
{
    mca_base_var_t *var_a, *var_b;
    int var_ai, var_bi;


    project = NULL;

    var_ai = mca_base_var_find (project, type_a, component_a, param_a);
    if (var_ai < 0) {
        return OPAL_ERR_NOT_FOUND;
    }

    var_bi = mca_base_var_find (project, type_b, component_b, param_b);
    if (var_bi < 0) {
        return OPAL_ERR_NOT_FOUND;
    }

    (void) var_get (var_ai, &var_a, true);
    (void) var_get (var_bi, &var_b, true);

    if (MCA_BASE_VAR_SOURCE_DEFAULT != var_a->mbv_source &&
        MCA_BASE_VAR_SOURCE_DEFAULT != var_b->mbv_source) {
        char *str_a, *str_b;


        str_a = source_name(var_a);


        str_b = source_name(var_b);


        opal_show_help("help-mca-var.txt",
                       "mutually-exclusive-vars",
                       true, var_a->mbv_full_name,
                       str_a, var_b->mbv_full_name,
                       str_b);


        free(str_a);
        free(str_b);

        return OPAL_ERR_BAD_PARAM;
    }

    return OPAL_SUCCESS;
}
