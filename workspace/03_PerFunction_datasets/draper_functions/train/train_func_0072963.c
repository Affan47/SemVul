start_output_pass (j_decompress_ptr cinfo)
{
#ifdef BLOCK_SMOOTHING_SUPPORTED
  my_coef_ptr coef = (my_coef_ptr) cinfo->coef;


  if (coef->pub.coef_arrays != NULL) {
    if (cinfo->do_block_smoothing && smoothing_ok(cinfo))
      coef->pub.decompress_data = decompress_smooth_data;
    else
      coef->pub.decompress_data = decompress_data;
  }
#endif
  cinfo->output_iMCU_row = 0;
}
