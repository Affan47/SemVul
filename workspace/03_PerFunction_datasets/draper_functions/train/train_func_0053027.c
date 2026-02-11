xsh_spectrum_duplicate( xsh_spectrum * org )
{
  xsh_spectrum * result = NULL ;

  XSH_ASSURE_NOT_NULL( org ) ;


  XSH_CALLOC( result, xsh_spectrum, 1 ) ;

  result->lambda_min = org->lambda_min;
  result->lambda_max = org->lambda_max;
  result->lambda_step = org->lambda_step;
  result->size_lambda = org->size_lambda ;
  result->slit_min = org->slit_min;
  result->slit_max = org->slit_max;
  result->size = org->size;
  result->size_slit = org->size_slit ;
  check( result->flux = cpl_image_duplicate( org->flux ) ) ;
  check( result->flux_header = cpl_propertylist_duplicate( org->flux_header ));
  check( result->errs = cpl_image_duplicate( org->errs ) ) ;
  check( result->errs_header = cpl_propertylist_duplicate( org->errs_header ));
  check( result->qual = cpl_image_duplicate( org->qual ) ) ;
  check( result->qual_header = cpl_propertylist_duplicate( org->qual_header ));

 cleanup:
  return result ;
}
