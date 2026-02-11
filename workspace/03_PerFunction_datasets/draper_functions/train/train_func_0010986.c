group_find (const char *project_name, const char *framework_name,
                       const char *component_name, bool invalidok)
{
    char *full_name;
    int ret, index=0;

    if (!mca_base_var_initialized) {
        return OPAL_ERR_NOT_FOUND;
    }


    project_name = NULL;

    ret = mca_base_var_generate_full_name4(project_name, framework_name, component_name,
                                           NULL, &full_name);
    if (OPAL_SUCCESS != ret) {
        return OPAL_ERROR;
    }

    ret = group_find_by_name(full_name, &index, invalidok);
    free (full_name);

    return (0 > ret) ? ret : index;
}
