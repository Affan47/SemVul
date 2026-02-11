giscience_create(cpl_plugin* plugin)
{

    cpl_recipe* recipe = (cpl_recipe*)plugin;

    cpl_parameter* p = NULL;


    giraffe_error_init();


    recipe->parameters = cpl_parameterlist_new();
    cx_assert(recipe->parameters != NULL);


    giraffe_bias_config_add(recipe->parameters);


    giraffe_extract_config_add(recipe->parameters);


    giraffe_flat_config_add(recipe->parameters);


    giraffe_rebin_config_add(recipe->parameters);


    p = cpl_parameter_new_value("giraffe.siwc.apply",
                                CPL_TYPE_BOOL,
                                "Enable simultaneous wavelength calibration "
                                "correction.",
                                "giraffe.siwc",
                                TRUE);

    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "siwc-apply");
    cpl_parameterlist_append(recipe->parameters, p);

    giraffe_sgcalibration_config_add(recipe->parameters);


    giraffe_fov_config_add(recipe->parameters);

    return 0;

}
