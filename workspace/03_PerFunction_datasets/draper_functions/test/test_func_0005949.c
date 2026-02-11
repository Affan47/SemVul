xsh_frame_table_monitor_flux_qc_ext(cpl_table* table,
				    const char* colw,
				    const char* colf,
				    const char* prefix,
				    xsh_instrument* instrument)
{
  cpl_propertylist* header=NULL;

  XSH_ASSURE_NOT_NULL_MSG(table,"Null input table");
  header=cpl_propertylist_new();
  check(cpl_table_cast_column(table,colw,"W",CPL_TYPE_DOUBLE));
  check(cpl_table_cast_column(table,colf,"F",CPL_TYPE_DOUBLE));

  if ( xsh_instrument_get_arm(instrument) == XSH_ARM_UVB){

    check( xsh_table_monitor_flux_qc(table,450,470,prefix,1,&header));
    check( xsh_table_monitor_flux_qc(table,510,530,prefix,2,&header));

  }
  else if ( xsh_instrument_get_arm(instrument) == XSH_ARM_VIS){

    check( xsh_table_monitor_flux_qc(table,672,680,prefix,1,&header));
    check( xsh_table_monitor_flux_qc(table,745,756,prefix,2,&header));
    check( xsh_table_monitor_flux_qc(table,992,999,prefix,3,&header));

  }
  else if ( xsh_instrument_get_arm(instrument) == XSH_ARM_NIR){

    check( xsh_table_monitor_flux_qc(table,1514,1548,prefix,1,&header));
    check( xsh_table_monitor_flux_qc(table,2214,2243,prefix,2,&header));

  }

  cpl_table_erase_column(table,"W");
  cpl_table_erase_column(table,"F");

cleanup:
  if(cpl_error_get_code() != CPL_ERROR_NONE) {
    return NULL;
  } else {
    return header;
  }
}
