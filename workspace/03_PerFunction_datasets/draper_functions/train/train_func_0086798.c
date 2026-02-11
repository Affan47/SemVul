xsh_params_monitor(xsh_background_param* backg,
                   xsh_rectify_param * rectify_par)
{


  xsh_msg_dbg_low("bkg params: sampley=%d radius_y=%d",
	  backg->sampley,backg->radius_y);

  xsh_msg_dbg_low("bkg params: radius_x=%d",
	  backg->radius_x);

  xsh_msg_dbg_low("rectify params: radius=%g bin_lambda=%g bin_space=%g",
	  rectify_par->rectif_radius,rectify_par->rectif_bin_lambda,
	  rectify_par->rectif_bin_space);

  return cpl_error_get_code();

}
