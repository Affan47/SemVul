irplib_mkmaster_dark_qc(const cpl_imagelist* raw_images,
    cpl_imagelist* preproc_images,
    const cpl_parameterlist* parameters,
     const int pr_num_x, const int pr_num_y,
    const int pr_box_sx, const int pr_box_sy, const char* recipe_id,
    cpl_table* qclog) {

   cpl_ensure_code(qclog !=NULL, CPL_ERROR_NULL_INPUT);
   cpl_ensure_code(recipe_id !=NULL, CPL_ERROR_NULL_INPUT);
   cpl_ensure_code(parameters !=NULL, CPL_ERROR_NULL_INPUT);

  int i = 0;
  cpl_image* current_dark = 0;
  if (pr_num_x != 0 && pr_num_y != 0 && pr_box_sx != 0 && pr_box_sy != 0) {
    for (i = 0; i < cpl_imagelist_get_size(raw_images); i++) {
      current_dark = cpl_image_duplicate(
          cpl_imagelist_get_const(preproc_images, i));
      cpl_msg_info(cpl_func, "Calculating QC parameters on raw dark frame %d",
          i);


    }
  }
  return cpl_error_get_code();
}
