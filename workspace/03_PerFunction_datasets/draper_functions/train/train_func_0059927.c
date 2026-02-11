kmo_fits_check_create(cpl_plugin *plugin)
{
    cpl_recipe *recipe;
    cpl_parameter *p;


    if (cpl_plugin_get_type(plugin) == CPL_PLUGIN_TYPE_RECIPE)
        recipe = (cpl_recipe *)plugin;
    else
        return -1;


    recipe->parameters = cpl_parameterlist_new();


    p = cpl_parameter_new_value("kmos.fits_check.data",
                                CPL_TYPE_INT,
                                "The extension whose data to print. "
                                "(0 is the empty primary extension, "
                                "-1 prints just all data extensions, "
                                "by default all headers and data of all "
                                "extensions are printed.",
                                "kmos.fits_check",
                                -2);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "data");
    cpl_parameter_disable(p, CPL_PARAMETER_MODE_ENV);
    cpl_parameterlist_append(recipe->parameters, p);


    p = cpl_parameter_new_value("kmos.fits_check.header",
                                CPL_TYPE_INT,
                                "The extension whose header to print"
                                "(0 is the empty primary extension, "
                                "-1 prints just all headers, "
                                "by default all headers and data of all "
                                "extensions are printed.",
                                "kmos.fits_check",
                                -2);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "header");
    cpl_parameter_disable(p, CPL_PARAMETER_MODE_ENV);
    cpl_parameterlist_append(recipe->parameters, p);

    return 0;
}
