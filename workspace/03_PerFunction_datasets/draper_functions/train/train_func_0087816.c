xsh_slice_offset_save(xsh_slice_offset *list,
  const char* filename, xsh_instrument *instrument)
{
  cpl_table *table = NULL;
  cpl_frame *result = NULL;
  const char *tag = NULL ;


  XSH_ASSURE_NOT_NULL( list);
  XSH_ASSURE_NOT_NULL( filename);
  XSH_ASSURE_NOT_NULL( instrument);


  check( table = cpl_table_new( 1));


  XSH_TABLE_NEW_COL( table, XSH_SLICE_OFFSET_TABLE_COLNAME_CEN_UP,
    XSH_SLICE_OFFSET_TABLE_UNIT_CEN_UP, CPL_TYPE_DOUBLE);
  XSH_TABLE_NEW_COL( table, XSH_SLICE_OFFSET_TABLE_COLNAME_CEN_DOWN,
    XSH_SLICE_OFFSET_TABLE_UNIT_CEN_DOWN, CPL_TYPE_DOUBLE);

  check( cpl_table_set_double( table, XSH_SLICE_OFFSET_TABLE_COLNAME_CEN_UP,
      0, list->cen_up));
  check( cpl_table_set_double( table, XSH_SLICE_OFFSET_TABLE_COLNAME_CEN_DOWN,
      0, list->cen_down));


  check( cpl_table_save( table, list->header, NULL, filename,
    CPL_IO_DEFAULT));


  tag = XSH_GET_TAG_FROM_ARM( XSH_SLICE_OFFSET, instrument);

  check( result = xsh_frame_product( filename, tag,
    CPL_FRAME_TYPE_TABLE, CPL_FRAME_GROUP_PRODUCT,
    CPL_FRAME_LEVEL_TEMPORARY));

  cleanup:
    XSH_TABLE_FREE(table);
    return result ;
}
