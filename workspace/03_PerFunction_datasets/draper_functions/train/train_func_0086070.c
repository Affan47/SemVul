sinfo_utl_cube_arith_create(cpl_plugin * plugin)
{
    cpl_recipe      * recipe ;
    cpl_parameter   * p ;


    if (cpl_plugin_get_type(plugin) == CPL_PLUGIN_TYPE_RECIPE)
        recipe = (cpl_recipe *)plugin ;
    else return -1 ;
    cpl_error_reset();
    irplib_reset();

    recipe->parameters = cpl_parameterlist_new() ;


    p = cpl_parameter_new_value("sinfoni.sinfo_utl_cube_arith.op",
                                CPL_TYPE_STRING,
                                "A possible operation: "
                                "`/','*','+' or `-'",
                                "sinfoni.sinfo_utl_cube_arith","/");
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "op") ;
    cpl_parameterlist_append(recipe->parameters, p) ;


    p = cpl_parameter_new_value("sinfoni.sinfo_utl_cube_arith.value",
                                CPL_TYPE_DOUBLE, "A constant to add",
                                "sinfoni.sinfo_utl_cube_arith", 99999.0) ;
    cpl_parameter_set_alias(p, CPL_PARAMETER_MODE_CLI, "value") ;
    cpl_parameterlist_append(recipe->parameters, p) ;


    return 0;
}
