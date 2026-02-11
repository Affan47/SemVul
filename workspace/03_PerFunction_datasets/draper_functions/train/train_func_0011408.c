xsh_array_clip_median( cpl_array *array,
                       double kappa,
                       int niter,
                       double frac_min,
                       double *median,
                       double *stdev)
{
  int  i, j, size;
  double median_val;
  double sigma, frac;
  int *flags = NULL;
  int nb_rejected = 0, total_rejected=0;
  double* pval=NULL;

  XSH_ASSURE_NOT_NULL( array);
  XSH_ASSURE_NOT_NULL( median);
  XSH_ASSURE_NOT_NULL( stdev);

  check( median_val = cpl_array_get_median( array));
  check( sigma = cpl_array_get_stdev( array));
  check( size =  cpl_array_get_size( array));

  XSH_CALLOC( flags, int, size);

  xsh_msg("Iteration %d/%d", 0, niter);
  xsh_msg("Accepted fraction %f Median %f sigma %f", 1.0, median_val, sigma);
  check(pval=cpl_array_get_data_double(array));
  for( i=1; i<= niter; i++) {
    xsh_msg("Iteration %d/%d", i, niter);
    nb_rejected = 0;
    for( j=0; j< size; j++){

      if ( flags[j] == 0 && fabs( pval[j]-median_val) > kappa*sigma){
        nb_rejected++;
        flags[j]=1;
        check( cpl_array_set_invalid( array, j));
      }
    }
    if ( nb_rejected == 0){
      xsh_msg("No more points are rejected. Iterations are stopped.");
      break;
    }
    total_rejected += nb_rejected;
    frac = 1-(double)total_rejected/(double)size;
    if (frac < frac_min){
      xsh_msg("Minimal fraction of accepted points %f is reached (%f). Iterations are stopped",
        frac_min, frac);
      break;
    }
    check( median_val = cpl_array_get_median( array));
    check( sigma = cpl_array_get_stdev( array));
    xsh_msg("Accepted fraction %f Median %f sigma %f", frac, median_val, sigma);
  }
  xsh_msg("End of clipping : Median %f sigma %f", median_val, sigma);
  *median = median_val;
  *stdev = sigma;

  cleanup:
    XSH_FREE( flags);
    return;
}
