kmo_wave_cal_create(cpl_plugin *plugin)
{
    cpl_recipe *recipe;
    cpl_parameter *p;


    if (cpl_plugin_get_type(plugin) == CPL_PLUGIN_TYPE_RECIPE)
        recipe = (cpl_recipe *)plugin;
    else
        return -1;


    recipe->parameters = cpl_parameterlist_new();


    p = cpl_parameter_new_value("kmos.kmo_wave_cal.order",
                                CPL_TYPE_INT,
                                "The polynomial order to use for the fit of "
                                "the wavelength solution. 0: (default) The "
                                "appropriate order is chosen automatically "
                                "depending on the waveband. Otherwise an order "
                                "of 6 is recommended, except for IZ-band, there "
                                "order 4 should be used",
                                "kmos.kmo_wave_cal",
                                0);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "order");
    cpl_parameter_disable(p, CPL_PARAMETER_MODE_ENV);
    cpl_parameterlist_append(recipe->parameters, p);

    p = cpl_parameter_new_value("kmos.kmo_wave_cal.dev_flip",
                                CPL_TYPE_BOOL,
                                "Set this parameter to TRUE if the wavelengths"
                                " are ascending on the detector from top to "
                                "bottom.",
                                "kmos.kmo_wave_cal",
                                FALSE);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "dev_flip");
    cpl_parameter_disable(p, CPL_PARAMETER_MODE_ENV);
    cpl_parameterlist_append(recipe->parameters, p);

    p = cpl_parameter_new_value("kmos.kmo_wave_cal.dev_disp",
                                CPL_TYPE_DOUBLE,
                                "The expected dispersion of the wavelength "
                                "in microns/pixel. If the default isn't "
                                "changed it will automatically be selected "
                                "upon header keywords.",
                                "kmos.kmo_wave_cal",
                                -1.0);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "dev_disp");
    cpl_parameter_disable(p, CPL_PARAMETER_MODE_ENV);
    cpl_parameterlist_append(recipe->parameters, p);


    p = cpl_parameter_new_value("kmos.kmo_wave_cal.suppress_extension",
                                CPL_TYPE_BOOL,
                                "Suppress arbitrary filename extension."
                                "(TRUE (apply) or FALSE (don't apply)",
                                "kmos.kmo_wave_cal",
                                FALSE);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "suppress_extension");
    cpl_parameter_disable(p, CPL_PARAMETER_MODE_ENV);
    cpl_parameterlist_append(recipe->parameters, p);


    kmo_band_pars_create(recipe->parameters,
                         "kmos.kmo_wave_cal");

    return 0;
}
