xsh_frame_image_ext_qc_trace_window(cpl_frame* frm_ima,
                                    xsh_instrument* instrument,
                                    const char* suffix,
                                    const int hsize,
                                    const int method)
{

  cpl_frame* result=NULL;
  cpl_table* table=NULL;
  cpl_table* table_tot=NULL;

  cpl_image* data_ima=NULL;
  const char* name=NULL;

  cpl_propertylist* phead=NULL;
  cpl_propertylist* xhead=NULL;

  char fname[256];
  char tag[50];
  int nbext=0;
  int k=0;
  int nrow=0;
  xsh_msg("Trace object position");
  check(name=cpl_frame_get_filename(frm_ima));
  nbext=cpl_frame_get_nextensions( frm_ima);

  table_tot=cpl_table_new(0);
  phead=cpl_propertylist_load(name,0);
  for(k=0;k<nbext;k+=3){
    nrow=cpl_table_get_nrow(table_tot);

    check(data_ima=cpl_image_load(name,CPL_TYPE_DOUBLE,0,k));
    xhead=cpl_propertylist_load(name,k);

    check(table=xsh_image_qc_trace_window(data_ima,xhead,hsize,method));
    if(k==0) check(cpl_table_copy_structure(table_tot,table));
    cpl_table_insert(table_tot,table,nrow);
    xsh_free_propertylist(&xhead);
    xsh_free_table(&table);
    xsh_free_image(&data_ima);
  }
  sprintf(tag,"OBJ_POS_ORD_%s_%s",
	  xsh_instrument_arm_tostring( instrument),suffix);
  sprintf(fname,"%s.fits",tag);

  check(cpl_table_save(table_tot,phead,NULL,fname,CPL_IO_DEFAULT));

  result=xsh_frame_product(fname,tag,CPL_FRAME_TYPE_TABLE,
			   CPL_FRAME_GROUP_PRODUCT,CPL_FRAME_LEVEL_FINAL);

  cleanup:

   xsh_free_propertylist(&phead);
   xsh_free_propertylist(&xhead);
   xsh_free_table(&table);
   xsh_free_table(&table_tot);
   xsh_free_image(&data_ima);

   return result;
}
