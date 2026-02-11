giraffe_localize_config_create(cpl_parameterlist *list)
{

    const cxchar *s;
    cpl_parameter *p;

    GiLocalizeConfig *config = NULL;


    if (list == NULL) {
        return NULL;
    }

    config = cx_calloc(1, sizeof *config);


    config->full = TRUE;
    config->centroid = TRUE;
    config->threshold = GILOCALIZE_THRESHOLD_LOCAL;


    p = cpl_parameterlist_find(list, "giraffe.localization.mode");
    s = cpl_parameter_get_string(p);
    if (strcmp(s, "siwc") == 0) {
        config->full = FALSE;
    }

    p = cpl_parameterlist_find(list, "giraffe.localization.start");
    config->start = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.retries");
    config->retries = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.binsize");
    config->binsize = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.ewidth");
    config->ewidth = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.ywidth");
    config->ywidth = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.center");
    s = cpl_parameter_get_string(p);
    if (!strcmp(s, "hwidth")) {
        config->centroid = FALSE;
    }

    p = cpl_parameterlist_find(list, "giraffe.localization.normalize");
    config->normalize = cpl_parameter_get_bool(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.threshold");
    s = cpl_parameter_get_string(p);

    if (strncmp(s, "global", 6) == 0) {
        config->threshold = GILOCALIZE_THRESHOLD_GLOBAL;
    }
    else if (strncmp(s, "row", 3) == 0) {
        config->threshold = GILOCALIZE_THRESHOLD_ROW;
    }
    else {
        config->threshold = GILOCALIZE_THRESHOLD_LOCAL;
    }

    p = cpl_parameterlist_find(list, "giraffe.localization.noise");
    config->noise = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.ron");
    config->ron = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.yorder");
    config->yorder = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.worder");
    config->worder = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.sigma");
    config->sigma = cpl_parameter_get_double(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.iterations");
    config->iterations = cpl_parameter_get_int(p);

    p = cpl_parameterlist_find(list, "giraffe.localization.fraction");
    config->fraction = cpl_parameter_get_double(p);

    return config;

}
