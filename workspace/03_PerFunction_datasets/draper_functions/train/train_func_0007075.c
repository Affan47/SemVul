xsh_get_master_dark_nir_via_noise(cpl_imagelist* dataList, cpl_frame* medFrame,
    cpl_parameterlist* parameters, xsh_clipping_param* noise_clipping,
    xsh_instrument* instrument,cpl_frame** noisyFrame) {
  cpl_frame* nirFrame = NULL;

  cpl_parameter* p = NULL;
  int llx = 0;
  int lly = 0;
  int urx = 0;
  int ury = 0;
  int iter = 0;
  int low_rej = 0;
  int high_rej = 0;
  cpl_image* noise_image = NULL;
  cpl_mask* bp_map_noise = NULL;
  cpl_propertylist* plist = NULL;
  const char* bp_map_noise_pro_catg = NULL;
  char bp_map_noise_name[256];


  xsh_msg_dbg_low(
      "Noise parameters: Sigma %lf, Niteration %d, \
   Fraction %lf, Diff %lf", noise_clipping->sigma, noise_clipping->niter, noise_clipping->frac, noise_clipping->diff);

  nirFrame = xsh_compute_noise_map(dataList, medFrame, noise_clipping,
      instrument,noisyFrame);


  p = cpl_parameterlist_find(parameters, "xsh.xsh_mdark.ref1_llx");
  llx = cpl_parameter_get_int(p);
  p = cpl_parameterlist_find(parameters, "xsh.xsh_mdark.ref1_lly");
  lly = cpl_parameter_get_int(p);
  p = cpl_parameterlist_find(parameters, "xsh.xsh_mdark.ref1_urx");
  urx = cpl_parameter_get_int(p);
  p = cpl_parameterlist_find(parameters, "xsh.xsh_mdark.ref1_ury");
  ury = cpl_parameter_get_int(p);
  p = cpl_parameterlist_find(parameters, "xsh.xsh_mdark.noise-clip-niter");
  iter = cpl_parameter_get_int(p);
  p = cpl_parameterlist_find(parameters, "xsh.xsh_mdark.noise-lower-rejection");
  low_rej = cpl_parameter_get_double(p);
  p = cpl_parameterlist_find(parameters, "xsh.xsh_mdark.noise-higher-rejection");
  high_rej = cpl_parameter_get_double(p);

  noise_image = xsh_image_search_bad_pixels_via_noise(dataList, iter, low_rej,
      high_rej, llx, lly, urx, ury);
  bp_map_noise = cpl_mask_threshold_image_create(noise_image,
      QFLAG_HOT_PIXEL - 1, QFLAG_HOT_PIXEL + 1);
  xsh_free_image(&noise_image);
  noise_image = cpl_image_new_from_mask(bp_map_noise);
  cpl_mask_not(bp_map_noise);
  xsh_bpmap_mask_bad_pixel(noise_image, bp_map_noise, QFLAG_HOT_PIXEL);


  cpl_image_threshold(noise_image, 1.1, DBL_MAX, 0, DBL_MAX);

  plist = cpl_propertylist_new();
  bp_map_noise_pro_catg = XSH_GET_TAG_FROM_ARM(XSH_BP_MAP_NP, instrument);
  sprintf(bp_map_noise_name, "%s.fits", bp_map_noise_pro_catg);
  xsh_pfits_set_pcatg(plist, bp_map_noise_pro_catg);
  check(cpl_image_save(noise_image,bp_map_noise_name,CPL_BPP_IEEE_FLOAT, plist,CPL_IO_DEFAULT));
  xsh_add_temporary_file(bp_map_noise_name);


  cleanup:
  xsh_free_mask(&bp_map_noise);
  xsh_free_propertylist(&plist);
  xsh_free_image(&noise_image);
  return nirFrame;

}
