xsh_flux_calibrate1D(cpl_frame* rect1D,
                   cpl_frame* atmext,
                   cpl_frame* response,
                   int mpar,
                   xsh_instrument* inst,
                   const char* rec_prefix,
                   cpl_frame** fcal_rect_1D,
                   cpl_frame** fcal_1D)
{

  char file_tag[256];
  char file_name[256];
  char arm_str[8] ;
  cpl_frame* nrm_1D=NULL;
  const char* tag=NULL;


  tag=cpl_frame_get_tag(rect1D);
  sprintf(arm_str,"%s",xsh_instrument_arm_tostring(inst));
  xsh_msg("tag=%s",tag);
  if(strstr(tag,XSH_ORDER_OXT1D) == NULL) {
     sprintf(file_tag,"%s_%s_%s",rec_prefix,XSH_NORM_ORDER1D,arm_str);
  } else {
     sprintf(file_tag,"%s_%s_%s",rec_prefix,XSH_NORM_OXT1D,arm_str);
  }
  xsh_msg("file_tag1=%s",file_tag);
  sprintf(file_name,"%s.fits",file_tag);
  xsh_add_temporary_file(file_name);

  check(nrm_1D=xsh_normalize_spectrum_ord(rect1D,atmext,1,inst,file_tag));
  if(strstr(tag,XSH_ORDER_OXT1D) == NULL) {
     sprintf(file_tag,"%s_%s_%s",rec_prefix,XSH_FLUX_ORDER1D,arm_str);
  } else {
     sprintf(file_tag,"%s_%s_%s",rec_prefix,XSH_FLUX_OXT1D,arm_str);
  }
  sprintf(file_name,"%s.fits",file_tag);


  check(*fcal_rect_1D=xsh_util_multiply_by_response_ord(nrm_1D,response,file_tag));
  check(*fcal_1D= xsh_merge_ord(*fcal_rect_1D,inst,mpar,rec_prefix));
  xsh_msg("file_tag2=%s",file_tag);


cleanup:
  xsh_free_frame(&nrm_1D);
  return cpl_error_get_code();

}
