xsh_check_afc( int check_flag, cpl_frame *model_frame,
  cpl_frame *sci_frame, cpl_frameset *wave_frameset,
  cpl_frame *order_tab_frame, cpl_frame *disp_tab_frame,
  xsh_instrument *instrument)
{
  int i;

  if (check_flag) {
     if( model_frame!=NULL) {
       check(xsh_frame_check_model_cfg_is_afc_corrected(model_frame));
       check(xsh_frame_check_model_cfg_is_proper_for_sci(model_frame,
         sci_frame,instrument));
     }
     else {
      for(i=0; i< 3; i++){
	cpl_frame *wavesol_frame = NULL;

	wavesol_frame = cpl_frameset_get_frame( wave_frameset, i);
        check(xsh_frame_check_model_cfg_is_afc_corrected(wavesol_frame));
        check(xsh_frame_check_model_cfg_is_proper_for_sci(wavesol_frame,
                                                       sci_frame,instrument));
      }
      check(xsh_frame_check_model_cfg_is_afc_corrected( order_tab_frame));
      check(xsh_frame_check_model_cfg_is_proper_for_sci( order_tab_frame,
                                                       sci_frame,instrument));
      if ( disp_tab_frame != NULL){
        check(xsh_frame_check_model_cfg_is_afc_corrected( disp_tab_frame));
        check(xsh_frame_check_model_cfg_is_proper_for_sci( disp_tab_frame,
                                                       sci_frame,instrument));
      }
    }
  }
  cleanup:
    return;
}
