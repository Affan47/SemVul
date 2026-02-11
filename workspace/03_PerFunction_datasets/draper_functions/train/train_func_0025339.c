vmimcalphot_create(cpl_plugin *plugin)
{

    cpl_recipe *recipe = (cpl_recipe *)plugin;

    cpl_parameter *p;

    cxint status = 0;


    recipe->parameters = cpl_parameterlist_new();
    if (recipe->parameters == NULL) {
        return 1;
    }


    p = cpl_parameter_new_value("vimos.Parameters.extinction",
                                CPL_TYPE_BOOL,
                                "Compute also extinction coefficient",
                                "vimos.Parameters",
                                FALSE);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "Extinction");
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CFG, "Extinction");
    cpl_parameterlist_append(recipe->parameters, p);


    p = cpl_parameter_new_value("vimos.Parameters.colorterm",
                                CPL_TYPE_BOOL,
                                "Compute also color term",
                                "vimos.Parameters",
                                FALSE);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "ColorTerm");
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CFG, "ColorTerm");
    cpl_parameterlist_append(recipe->parameters, p);


    p = cpl_parameter_new_value("vimos.Parameters.usecolorterm",
                                CPL_TYPE_BOOL,
                                "Use color term in zeropoint computation",
                                "vimos.Parameters",
                                FALSE);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "UseColorTerm");
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CFG, "UseColorTerm");
    cpl_parameterlist_append(recipe->parameters, p);


    status = vmCplRecipeStart(cpl_plugin_get_name(plugin), VERSION);

    if (status) {
        return 1;
    }

    return 0;

}
