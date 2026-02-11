sinfo_auto_size_cube5(object_config * cfg,
                    float* ref_offx, float* ref_offy,
                    float* min_offx, float* min_offy,
                    float* max_offx, float* max_offy)
{

  char* name =NULL;
  int n=0;
  float offx=0;
  float offy=0;

  cpl_propertylist * plist=NULL;
  sinfo_msg ("Automatic computation of output cube size") ;
  for ( n = 0 ; n < cfg->nframes ; n++ ) {
    name = cfg->framelist[n] ;
    plist=cpl_propertylist_load(name,0);
    offx = sinfo_pfits_get_cumoffsetx(plist);
    if(cpl_error_get_code() != CPL_ERROR_NONE) {
      sinfo_msg_warning(" could not read fits header keyword cummoffsetx!");
      sinfo_msg_warning(" set it to  0");
      offx = 0;
      cpl_error_reset();

    }

    offy = sinfo_pfits_get_cumoffsety(plist);
    sinfo_free_propertylist(&plist);
    if(cpl_error_get_code() != CPL_ERROR_NONE) {
      sinfo_msg_warning(" could not read fits header keyword! cumoffsety") ;
      sinfo_msg_warning(" set it to 0");
      offy = 0;
      cpl_error_reset();

    }


    if(n==0) {
      *min_offx=offx;
      *min_offy=offy;
      *max_offx=offx;
      *max_offy=offy;
    } else {
      if(offx > *max_offx) *max_offx=offx;
      if(offy > *max_offy) *max_offy=offy;
      if(offx < *min_offx) *min_offx=offx;
      if(offy < *min_offy) *min_offy=offy;
    }
  }
  *ref_offx=(*min_offx+*max_offx)/2;
  *ref_offy=(*min_offy+*max_offy)/2;

  if(cfg->size_x == 0) cfg->size_x=2*floor(*max_offx-*min_offx+0.5)+64 ;


  if(cfg->size_y == 0) cfg->size_y=2*floor(*max_offy-*min_offy+0.5)+64 ;

  sinfo_msg("Output cube size: %d x %d",cfg->size_x,cfg->size_y);
  sinfo_msg("Ref offset. x: %f y: %f",*ref_offx,*ref_offy);
  sinfo_msg("Max offset. x: %f y: %f",*max_offx,*max_offy);
  sinfo_msg("Min offset. x: %f y: %f",*min_offx,*min_offy);
  return 0;


}
