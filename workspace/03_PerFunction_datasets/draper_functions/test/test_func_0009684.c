xsh_parameters_background_create( const char* recipe_id,
  cpl_parameterlist* list)
{


  XSH_ASSURE_NOT_NULL(list);


  assure(list != NULL,CPL_ERROR_NULL_INPUT,"parameters list is NULL");

  check( xsh_parameters_new_range_int( list, recipe_id,
      "background-edges-margin",
      1,0,15,
      "X margin to order edge to define background sampling points"));

  check( xsh_parameters_new_range_int( list, recipe_id,
     "background-poly-deg-y",
                                       9,0,15,
     "Poly mode fit deg along Y."));

  check( xsh_parameters_new_range_int( list, recipe_id,
      "background-poly-deg-x",
                                 9,0,15,
      "Poly mode fit deg along X."));

  check( xsh_parameters_new_range_double( list, recipe_id,
       "background-poly-kappa",
                                    10.0,0,100,
       "Poly mode kappa value of kappa-sigma-clip outliers removal."));


  cleanup:
    return;
}
