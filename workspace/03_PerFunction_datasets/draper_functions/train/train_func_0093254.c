cumulate_qc_parameter( int order, xsh_order_list * list,
				   CENTROIDS_STRUCT * pcent, int npts )
{
  int j, absorder ;
  double diff ;
  double * Delta0 ;
  int prevSize ;

  absorder = list->list[order].absorder ;
  xsh_msg_dbg_low( " Cumulate: Order %d, Nb of Points: %d", absorder, npts ) ;
  prevSize = DeltaSize ;

  DeltaSize += npts ;
  if ( order == 0 ) {
    XSH_CALLOC( Deltas, double, DeltaSize ) ;
    XSH_CALLOC( PosX, double, DeltaSize ) ;
    XSH_CALLOC( PosY, double, DeltaSize ) ;
    XSH_CALLOC( Orders, int, DeltaSize ) ;
    XSH_CALLOC( XorderPos, double, DeltaSize ) ;
  }
  else {

    Deltas = cpl_realloc( Deltas, DeltaSize*sizeof(double) ) ;
    PosX = cpl_realloc( PosX, DeltaSize*sizeof(double) ) ;
    PosY = cpl_realloc( PosY, DeltaSize*sizeof(double) ) ;
    Orders = cpl_realloc( Orders, DeltaSize*sizeof(int) ) ;
    XorderPos = cpl_realloc( XorderPos, DeltaSize*sizeof(double) ) ;
  }
  xsh_msg_dbg_low( "Cumulated points: %d", DeltaSize ) ;
  Delta0 = Deltas + prevSize ;


  for( j = 0 ; j<npts ; j++, pcent++ ) {
    double x1 ;
    double y ;

    y = pcent->position ;
    x1 = cpl_polynomial_eval_1d( list->list[order].cenpoly, y, NULL ) ;
    diff= ( x1 - pcent->centervalue ) ;

    xsh_msg_dbg_medium( "    ---- Y = %lf, x0 = %lf, x1 = %lf, diff = %lf", y,
		     pcent->centervalue, x1, diff ) ;
    *(Deltas+DeltaPoints) = diff ;
    *(PosX+DeltaPoints) = pcent->centervalue ;
    *(PosY+DeltaPoints) = y ;
    *(Orders+DeltaPoints) = absorder ;
    *(XorderPos+DeltaPoints) = x1 ;
    DeltaPoints++ ;
  }
  {

    cpl_vector *v_avg = NULL ;
    double residavg, residmax, residmin, residrms ;
    v_avg = cpl_vector_wrap( npts, Delta0 ) ;

    residavg = cpl_vector_get_mean( v_avg ) ;
    residmax = cpl_vector_get_max( v_avg ) ;
    residmin = cpl_vector_get_min( v_avg ) ;
    residrms = cpl_vector_get_stdev( v_avg ) ;
    xsh_msg_dbg_low( " Residuals for Order %d:", absorder ) ;
    xsh_msg_dbg_low( "     Mean: %lf, Max: %lf, Min: %lf, Rms: %lf",
		     residavg, residmax, residmin, residrms ) ;
    xsh_msg_dbg_low( "   StartY: %d, Endy: %d", list->list[order].starty,
		     list->list[order].endy ) ;
    cpl_vector_unwrap( v_avg ) ;
  }

 cleanup:
  return ;
}
