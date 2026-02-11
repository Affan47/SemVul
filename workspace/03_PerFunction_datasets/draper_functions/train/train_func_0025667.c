xsh_parameters_subtract_sky_single_get_first( const char* recipe_id,
						  cpl_parameterlist* list)
{
  int result = 0 ;


  assure(list != NULL,CPL_ERROR_NULL_INPUT,"parameters list is NULL");


  check(result = xsh_parameters_get_int( list, recipe_id,
    "sky-bspline-nbkpts-first"));

  cleanup:
    return result;

}
