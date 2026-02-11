giraffe_stacking_config_add(cpl_parameterlist *list)
{

    cpl_parameter *p;

    if (list == NULL) {
        return;
    }

    p = cpl_parameter_new_enum("giraffe.stacking.method",
                               CPL_TYPE_STRING,
                               "Stacking method: average, median, minmax or "
                               "ksigma",
                               "giraffe.stacking",
                               "average", 4, "average", "median",
                               "minmax", "ksigma");

    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "stack-method");
    cpl_parameterlist_append(list, p);

    p = cpl_parameter_new_value("giraffe.stacking.ksigma.low",
                                CPL_TYPE_DOUBLE,
                                "Lower threshold multiplier for method "
                                "ksigma",
                                "giraffe.stacking.ksigma",
                                5.0);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "stack-ksigmalow");
    cpl_parameterlist_append(list, p);

    p = cpl_parameter_new_value("giraffe.stacking.ksigma.high",
                                CPL_TYPE_DOUBLE,
                                "Upper threshold multiplier for method "
                                "ksigma",
                                "giraffe.stacking.ksigma",
                                5.0);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "stack-ksigmahigh");
    cpl_parameterlist_append(list, p);

    p = cpl_parameter_new_value("giraffe.stacking.minmax.minimum",
                                CPL_TYPE_INT,
                                "Minimum rejection level for method minmax",
                                "giraffe.stacking.minmax",
                                1);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "stack-minreject");
    cpl_parameterlist_append(list, p);

    p = cpl_parameter_new_value("giraffe.stacking.minmax.maximum",
                                CPL_TYPE_INT,
                                "Maximum rejection level for method minmax",
                                "giraffe.stacking.minmax",
                                1);
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "stack-maxreject");
    cpl_parameterlist_append(list, p);

    return;

}
