fors_identify_method_new(const cpl_parameterlist *parameters, const char *context)
{
    identify_method *im = cpl_malloc(sizeof(*im));
    const char *name = NULL;

    cpl_msg_info(cpl_func, "Identification parameters:");


    im->search = 5.0;


    im->max_search = 5.0;


    cpl_msg_indent_more();
    name = cpl_sprintf("%s.%s", context, "maxoffset");
    im->max_offset = dfs_get_parameter_double_const(parameters, name);
    cpl_free((void *)name); name = NULL;
    cpl_msg_indent_less();


    assure( !cpl_error_get_code(), return NULL, NULL );

    return im;
}
