xsh_parameters_subtract_sky_single_get(
  const char* recipe_id, cpl_parameterlist* list)
{
  xsh_subtract_sky_single_param *result = NULL ;
  const char* par_method = NULL;
  const char* bspline_sampling = NULL;


  XSH_ASSURE_NOT_NULL( recipe_id);
  XSH_ASSURE_NOT_NULL( list);


  XSH_MALLOC( result, xsh_subtract_sky_single_param, 1);


  check( result->nbkpts1 = xsh_parameters_get_int( list, recipe_id,
    "sky-bspline-nbkpts-first"));
  check( result->nbkpts2 = xsh_parameters_get_int( list, recipe_id,
    "sky-bspline-nbkpts-second"));
  check( result->bezier_spline_order = xsh_parameters_get_int( list, recipe_id,
    "sky-bspline-order"));
  check( result->niter = xsh_parameters_get_int( list, recipe_id,
    "sky-bspline-niter"));
  check( result->kappa =  xsh_parameters_get_double( list, recipe_id,
    "sky-bspline-kappa"));


  check( par_method = xsh_string_toupper(xsh_parameters_get_string(list,
                                                                   recipe_id,
                                                                   "sky-method")
            ));


  if ( strcmp( SKY_METHOD_PRINT(BSPLINE_METHOD), par_method) == 0){
    result->method = BSPLINE_METHOD;
  }
  else if (strcmp( SKY_METHOD_PRINT(MEDIAN_METHOD), par_method) == 0){
    result->method = MEDIAN_METHOD;
  }
  else {
    xsh_error_msg("WRONG parameter sky_method %s",par_method);
  }

  check( bspline_sampling = xsh_parameters_get_string( list, recipe_id,
    "bspline-sampling"));
  if ( strcmp( BSPLINE_SAMPLING_PRINT(UNIFORM), bspline_sampling) == 0){
    result->bspline_sampling = BSPLINE_METHOD;
  }
  else if (strcmp( BSPLINE_SAMPLING_PRINT(FINE), bspline_sampling) == 0){
    result->bspline_sampling = FINE;
  }
  else {
    xsh_error_msg("WRONG parameter bspline-sampling %s",bspline_sampling);
  }


  check( result->median_hsize =  xsh_parameters_get_int( list, recipe_id,
    "sky-median-hsize"));
  check( result->slit_edges_mask =  xsh_parameters_get_double( list,
    recipe_id,
    "sky-slit-edges-mask"));

  check( result->pos1 =  xsh_parameters_get_double( list,
    recipe_id,
    "sky-position1"));
  check( result->hheight1 =  xsh_parameters_get_double( list,
    recipe_id,
    "sky-hheight1"));
  check( result->pos2 =  xsh_parameters_get_double( list,
    recipe_id,
    "sky-position2"));
  check( result->hheight2 =  xsh_parameters_get_double( list,
    recipe_id,
    "sky-hheight2"));

  cleanup:
    if(cpl_error_get_code() != CPL_ERROR_NONE){
      cpl_free(result);
      result = NULL;
    }
    return result;
}
