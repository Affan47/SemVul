vmspphot_create(cpl_plugin *plugin)
{

    cpl_recipe *recipe = (cpl_recipe *)plugin;

    cpl_parameter *p;

    cxint status = 0;


    recipe->parameters = cpl_parameterlist_new();
    if (recipe->parameters == NULL) {
        return 1;
    }


    p = cpl_parameter_new_value("vimos.Parameters.flux.response",
                                CPL_TYPE_BOOL,
                                "Apply instrument response.",
                                "vimos.Parameters",
                                TRUE);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "ApplyResponse");
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CFG, "ApplyResponse");
    cpl_parameterlist_append(recipe->parameters, p);


    status = vmCplRecipeStart(cpl_plugin_get_name(plugin), VERSION);

    if (status) {
        return 1;
    }

    return 0;

}
