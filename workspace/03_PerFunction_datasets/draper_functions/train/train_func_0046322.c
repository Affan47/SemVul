xsh_spectrum1D_create( double lambda_min, double lambda_max,
  double lambda_step)
{
  xsh_spectrum1D* result = NULL;


  XSH_ASSURE_NOT_ILLEGAL( lambda_min >= 0.0 && lambda_min <= lambda_max);
  XSH_ASSURE_NOT_ILLEGAL( lambda_step >=0);

  XSH_CALLOC(result, xsh_spectrum1D,1);

  result->lambda_min = lambda_min;
  result->lambda_max = lambda_max;
  result->lambda_step = lambda_step;

  XSH_NEW_PROPERTYLIST( result->flux_header);
  check( xsh_pfits_set_crpix1( result->flux_header, 0.5));
  check( xsh_pfits_set_crval1( result->flux_header, lambda_min));
  check( xsh_pfits_set_cdelt1( result->flux_header, lambda_step));

  XSH_NEW_PROPERTYLIST( result->errs_header);
  check( xsh_pfits_set_extname ( result->errs_header, "ERRS"));
  XSH_NEW_PROPERTYLIST( result->qual_header);
  check( xsh_pfits_set_extname ( result->qual_header, "QUAL"));


  result->size = (int)((lambda_max-lambda_min)/lambda_step+0.5);

  check( result->flux = cpl_image_new( result->size, 1, CPL_TYPE_DOUBLE));
  check( result->errs = cpl_image_new( result->size, 1, CPL_TYPE_DOUBLE));
  check( result->qual = cpl_image_new( result->size, 1, CPL_TYPE_INT));

  cleanup:
    if (cpl_error_get_code() != CPL_ERROR_NONE) {
      xsh_spectrum1D_free(&result);
    }
    return result;
}
