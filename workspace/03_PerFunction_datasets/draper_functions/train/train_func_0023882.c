xsh_parameters_detect_continuum_get(
  const char* recipe_id, cpl_parameterlist* list)
{
  xsh_detect_continuum_param* result = NULL;


  XSH_ASSURE_NOT_NULL( list);


  XSH_MALLOC( result, xsh_detect_continuum_param, 1);


  check( result->search_window = xsh_parameters_get_int( list, recipe_id,
    "detectcontinuum-search-win-hsize"));
  check( result->fit_window = xsh_parameters_get_int( list, recipe_id,
    "detectcontinuum-fit-win-hsize"));
  check( result->fit_threshold = xsh_parameters_get_double( list, recipe_id,
    "detectcontinuum-center-thresh-fac"));
  check( result->running_window = xsh_parameters_get_int( list, recipe_id,
    "detectcontinuum-running-win-hsize"));
  check( result->poly_degree = xsh_parameters_get_int( list, recipe_id,
    "detectcontinuum-ordertab-deg-y"));
  check( result->poly_step = xsh_parameters_get_int( list, recipe_id,
    "detectcontinuum-ordertab-step-y"));


  cleanup:
    if(cpl_error_get_code() != CPL_ERROR_NONE){
      XSH_FREE(result);
    }
    return result;
}
