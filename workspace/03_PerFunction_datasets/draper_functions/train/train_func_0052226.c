xsh_create_master_dark (cpl_frame * medFrame, xsh_instrument* instr,
			cpl_parameterlist* parameters,
                        cpl_frame* crh_frm,cpl_frame* bpm_frm)
{


  xsh_pre *medPre = NULL;
  double exptime = 0.0;
  cpl_frame* resFrame = NULL;
  const  char* tag = XSH_GET_TAG_FROM_ARM (XSH_MASTER_DARK, instr);
  char* finalName = NULL;

  XSH_ASSURE_NOT_NULL(medFrame);
  XSH_ASSURE_NOT_NULL(instr);

  check(medPre = xsh_pre_load (medFrame,instr));
  XSH_ASSURE_NOT_NULL(medPre);

  exptime = medPre->exptime;


  if ( instr->arm != XSH_ARM_NIR ) {
    check_msg (cpl_image_divide_scalar (medPre->data, exptime),
	       "Cant divide median image by exptime %lf", exptime);
    check_msg (cpl_image_divide_scalar (medPre->errs, exptime),
	       "Cant divide median image by exptime %lf", exptime);


    xsh_msg_dbg_high ("Set EXPTIME = 1.");
    check(xsh_pfits_set_exptime (medPre->data_header, (double) 1.));
    check(xsh_pfits_set_exptime (medPre->errs_header, (double) 1.));
  }


 if ( xsh_instrument_get_arm(instr) == XSH_ARM_NIR ) {
    check(finalName =cpl_sprintf("%s_%s.fits",XSH_MASTER_DARK,
				xsh_instrument_arm_tostring(instr)));
 } else {


    check(finalName =cpl_sprintf("%s_%s.fits",XSH_MASTER_DARK,
				xsh_instrument_arm_tostring(instr)));
 }


  check(set_masterdark_qc (medPre, instr,parameters,crh_frm,bpm_frm));


  check ( resFrame = xsh_pre_save (medPre, finalName, tag,0 ));

 assure (resFrame != NULL, cpl_error_get_code (), "Cant save PRE");
  xsh_msg_dbg_high ("PRE frame saved as file %s", finalName);

  check(cpl_frame_set_level (resFrame, CPL_FRAME_LEVEL_FINAL));
  check(cpl_frame_set_tag (resFrame, tag));

 cleanup:
  if (cpl_error_get_code() != CPL_ERROR_NONE){
    xsh_free_frame(&resFrame);
  }
  cpl_free(finalName);
  xsh_pre_free(&medPre);
  return resFrame;
}
