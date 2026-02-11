xsh_parameters_wavecal_margin_create(const char* recipe_id,
					  cpl_parameterlist* list)
{

  assure(list != NULL,CPL_ERROR_NULL_INPUT,"parameters list is NULL");


  check(xsh_parameters_new_range_int( list, recipe_id,
				      "followarclines-order-edges-mask",
				      WAVECAL_MARGIN_DEFAULT, 0, 20,
	  "Nb of pixels suppressed (X) from edges of search window."
	  "" ));

  cleanup:
    return;
}
