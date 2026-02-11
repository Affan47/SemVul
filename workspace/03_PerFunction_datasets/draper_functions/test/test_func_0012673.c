xsh_shift_offsettab( cpl_frameset *shiftifu_frameset,
  double offset_low, double offset_up)
{
  cpl_frameset *result = NULL;
  cpl_frame *lo_frame = NULL;
  const char *lo_name = NULL;
  cpl_table *lo_table = NULL;
  double *lo_data = NULL;
  cpl_frame *up_frame = NULL;
  const char *up_name = NULL;
  cpl_table *up_table = NULL;
  double *up_data = NULL;
  int i, size;
  cpl_propertylist *lo_header = NULL;
  cpl_propertylist *up_header = NULL;
  cpl_frame *prod_frame = NULL;

  lo_frame = cpl_frameset_get_frame(shiftifu_frameset,0);
  lo_name = cpl_frame_get_filename(lo_frame);
  xsh_msg("Name %s", lo_name);
  XSH_TABLE_LOAD( lo_table, lo_name);
  check( lo_data = cpl_table_get_data_double( lo_table,
    XSH_SHIFTIFU_COLNAME_SHIFTSLIT));

  up_frame = cpl_frameset_get_frame(shiftifu_frameset,2);
  up_name = cpl_frame_get_filename(up_frame);
  xsh_msg("Name %s", up_name);
  XSH_TABLE_LOAD( up_table, up_name);
  check( up_data = cpl_table_get_data_double( up_table,
    XSH_SHIFTIFU_COLNAME_SHIFTSLIT));

  size = cpl_table_get_nrow( lo_table);

  for( i=0; i<size; i++){
    lo_data[i] += offset_low;
    up_data[i] += offset_up;
  }

  lo_header = cpl_propertylist_load( lo_name,0);
  check( cpl_table_save( lo_table, lo_header, NULL, "tmp_OFFSET_TAB_LOW.fits", CPL_IO_DEFAULT));
  up_header = cpl_propertylist_load( up_name,0);
  check( cpl_table_save( up_table, up_header, NULL, "tmp_OFFSET_TAB_UP.fits", CPL_IO_DEFAULT));

  result = cpl_frameset_new();
  check(prod_frame = xsh_frame_product( "tmp_OFFSET_TAB_LOW.fits",
                                  "OFFSET_TAB",
                                   CPL_FRAME_TYPE_TABLE,
                                   CPL_FRAME_GROUP_PRODUCT,
                                   CPL_FRAME_LEVEL_TEMPORARY));
  cpl_frameset_insert( result, prod_frame);

  check(prod_frame = cpl_frame_duplicate( cpl_frameset_get_frame(shiftifu_frameset,1)));
  cpl_frameset_insert( result, prod_frame);

  check(prod_frame = xsh_frame_product( "tmp_OFFSET_TAB_UP.fits",
                                  "OFFSET_TAB",
                                   CPL_FRAME_TYPE_TABLE,
                                   CPL_FRAME_GROUP_PRODUCT,
                                   CPL_FRAME_LEVEL_TEMPORARY));
  cpl_frameset_insert( result, prod_frame);

  cleanup:
    if ( cpl_error_get_code() != CPL_ERROR_NONE){
      xsh_free_frameset( &result);
    }
    XSH_TABLE_FREE( lo_table);
    XSH_TABLE_FREE( up_table);
    xsh_free_propertylist( &lo_header);
    xsh_free_propertylist( &up_header);
    return result;
}
