xsh_flux_calibrate2D(cpl_frame* rect2D,
                   cpl_frame* atmext,
                   cpl_frame* response,
                   int mpar,
                   xsh_instrument* inst,
                   const char* rec_prefix,
                   cpl_frame** fcal_rect_2D,
                   cpl_frame** fcal_2D)
{


  char file_tag[256];
  char file_name[256];
  char arm_str[8] ;
  cpl_frame* nrm_2D=NULL;

  sprintf(arm_str,"%s",xsh_instrument_arm_tostring(inst));

  sprintf(file_tag,"%s_%s_%s",rec_prefix,XSH_NORM_ORDER2D,arm_str);
  sprintf(file_name,"%s.fits",file_tag);
  check(nrm_2D=xsh_normalize_spectrum_ord(rect2D,atmext,1,inst,file_tag));
  xsh_add_temporary_file(file_name);


  sprintf(file_tag,"%s_%s_%s",rec_prefix,XSH_FLUX_ORDER2D,arm_str);
  check(*fcal_rect_2D=xsh_util_multiply_by_response_ord(nrm_2D,response,file_tag));
  check(*fcal_2D = xsh_merge_ord(*fcal_rect_2D, inst,mpar,rec_prefix));

cleanup:
  xsh_free_frame(&nrm_2D);
  return cpl_error_get_code();


}
