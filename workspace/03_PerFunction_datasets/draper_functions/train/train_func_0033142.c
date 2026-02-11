giraffe_flat_config_create(cpl_parameterlist *list)
{

    cpl_parameter *p;

    GiFlatConfig *config = NULL;


    if (!list) {
        return NULL;
    }

    config = cx_calloc(1, sizeof *config);


    config->apply = FALSE;
    config->transmission = TRUE;


    p = cpl_parameterlist_find(list, "giraffe.flat.apply");
    config->apply = cpl_parameter_get_bool(p);

    p = cpl_parameterlist_find(list, "giraffe.flat.transmission");
    config->transmission = cpl_parameter_get_bool(p);

    config->load = config->apply || config->transmission;

    return config;

}
