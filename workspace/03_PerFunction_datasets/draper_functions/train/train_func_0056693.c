xsh_spectrum_2D_create( double lambda_min, double lambda_max,
  double lambda_step, double slit_min, double slit_max, double slit_step)
{
  xsh_spectrum* result = NULL;


  XSH_ASSURE_NOT_ILLEGAL( lambda_min >= 0.0 && lambda_min <= lambda_max);
  XSH_ASSURE_NOT_ILLEGAL( lambda_step >=0);
  XSH_ASSURE_NOT_ILLEGAL( slit_min <= slit_max);
  XSH_ASSURE_NOT_ILLEGAL( slit_step >=0);


  XSH_CALLOC(result, xsh_spectrum,1);

  result->lambda_min = lambda_min;
  result->lambda_max = lambda_max;
  result->lambda_step = lambda_step;
  result->slit_min = slit_min;
  result->slit_max =  slit_max;
  result->slit_step = slit_step;

  XSH_NEW_PROPERTYLIST( result->flux_header);
  check( xsh_pfits_set_crpix1( result->flux_header, 1.0));
  check( xsh_pfits_set_crval1( result->flux_header, lambda_min));
  check( xsh_pfits_set_cdelt1( result->flux_header, lambda_step));
  check( xsh_pfits_set_crpix2( result->flux_header, 1.0));
  check( xsh_pfits_set_crval2( result->flux_header, slit_min));
  check( xsh_pfits_set_cdelt2( result->flux_header, slit_step));
  check( xsh_pfits_set_ctype1( result->flux_header, "LINEAR"));
  check( xsh_pfits_set_ctype2( result->flux_header, "LINEAR"));
  check(xsh_set_cd_matrix2d(result->flux_header));

  XSH_NEW_PROPERTYLIST( result->errs_header);
  check( xsh_pfits_set_extname ( result->errs_header, "ERRS"));
  XSH_NEW_PROPERTYLIST( result->qual_header);
  check( xsh_pfits_set_extname ( result->qual_header, "QUAL"));


  result->size_lambda = (int)((lambda_max-lambda_min)/lambda_step+0.5)+1;
  result->size_slit = (int)((slit_max-slit_min)/slit_step+0.5)+1;
  result->size = result->size_lambda * result->size_slit;
  check( result->flux = cpl_image_new( result->size_lambda, result->size_slit,
    CPL_TYPE_DOUBLE));
  check( result->errs = cpl_image_new( result->size_lambda, result->size_slit,
    CPL_TYPE_DOUBLE));
  check( result->qual = cpl_image_new( result->size_lambda, result->size_slit,
    CPL_TYPE_INT));

  cleanup:
    if (cpl_error_get_code() != CPL_ERROR_NONE) {
      xsh_spectrum_free(&result);
    }
    return result;
}
