xsh_parameters_slit_limit_get( const char * recipe_id,
						      cpl_parameterlist* list )
{
  xsh_slit_limit_param * result = NULL ;


  XSH_ASSURE_NOT_NULL( recipe_id);
  XSH_ASSURE_NOT_NULL( list);

  XSH_MALLOC( result, xsh_slit_limit_param, 1);


  check( result->min_slit = xsh_parameters_get_double( list,recipe_id,
						      "min-slit"));
  check( result->max_slit = xsh_parameters_get_double( list,recipe_id,
						      "max-slit"));
 cleanup:
  if(cpl_error_get_code() != CPL_ERROR_NONE){
    XSH_FREE( result);
  }
  return result;
}
