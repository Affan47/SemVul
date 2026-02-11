xsh_order_frameset_by_date( cpl_frameset *frameset)
{
  int nb, i ;
  FRAME_DATE_IDX *frame_date = NULL;
  cpl_frameset *result = NULL ;
  cpl_propertylist *header = NULL;

  XSH_ASSURE_NOT_NULL( frameset);

  check( nb = cpl_frameset_get_size( frameset));
  if ( nb <= 1 ) {
    check( result = cpl_frameset_duplicate( frameset));
  }
  else{
    XSH_CALLOC( frame_date, FRAME_DATE_IDX, nb);


    for( i = 0 ; i < nb ; i++){
      const char *fname = NULL ;
      cpl_frame *frame = NULL ;
      const char *the_date = NULL;


      check( frame = cpl_frameset_get_frame( frameset, i));
      check( fname = cpl_frame_get_filename( frame));


      check( header = cpl_propertylist_load( fname, 0));

      check( the_date = xsh_pfits_get_date_obs( header));

      frame_date[i].frame_date = date_to_double( the_date);
      frame_date[i].frame_idx = i;
      frame_date[i].frame = frame;
      frame_date[i].frame_name = fname;

      xsh_free_propertylist( &header);
    }

    qsort( frame_date, nb, sizeof( FRAME_DATE_IDX ), compare_frame_date ) ;

    if ( xsh_debug_level_get() > XSH_DEBUG_LEVEL_NONE ) {
      for( i = 0 ; i<nb ; i++ ) {
        xsh_msg( "%d: %.9lf '%s'", frame_date[i].frame_idx,
          frame_date[i].frame_date, frame_date[i].frame_name);
      }
    }

    check( result = cpl_frameset_new() ) ;


    for( i = 0 ; i <nb ; i++ ){
      check( cpl_frameset_insert( result,
        cpl_frame_duplicate(frame_date[i].frame)));
    }
  }
  cleanup:
    if ( cpl_error_get_code() != CPL_ERROR_NONE){
      xsh_free_frameset( &result);
    }
    xsh_free_propertylist( &header);
    XSH_FREE( frame_date);
    return result;
}
