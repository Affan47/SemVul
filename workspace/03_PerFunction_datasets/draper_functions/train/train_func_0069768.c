xsh_detect_max_y( xsh_order_list* list,
                  int chunk_hsize,
                  cpl_polynomial *cen_poly,
                  int cen_start,
                  int cen_end,
                  xsh_pre *pre,
                  const int decode_bp,
                  int* maxy)
{
  int y;
  float flux_max;
  int *qual = NULL;


  XSH_ASSURE_NOT_NULL( cen_poly);
  XSH_ASSURE_NOT_NULL( pre);
  XSH_ASSURE_NOT_NULL( maxy);
  XSH_ASSURE_NOT_ILLEGAL( cen_start >=1);
  XSH_ASSURE_NOT_ILLEGAL( cen_end <= pre->ny);

  check( qual = cpl_image_get_data_int( pre->qual));
  flux_max = 0.0;
  for(y=cen_start+chunk_hsize; y<= cen_end-chunk_hsize; y++){
    int x;
    double flux, noise;

    check( x = xsh_order_list_eval_int( list, cen_poly, y));


    check( xsh_eval_y_avg_chunk( pre, x-1, y-1, chunk_hsize, 0,decode_bp,
      &flux, &noise));
    if ( flux > flux_max ){
      if ( (qual[x-1+(y-1)*pre->nx] & decode_bp) == 0 ){

      flux_max = flux;
      *maxy = y;
      }
    }
  }

  cleanup:
    return;
}
