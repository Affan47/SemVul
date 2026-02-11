xsh_spectrum1D_save( xsh_spectrum1D* s, const char* filename)
{
  cpl_frame *product_frame = NULL;

  XSH_ASSURE_NOT_NULL(s);
  XSH_ASSURE_NOT_NULL(filename);


  check_msg (cpl_image_save ( s->flux, filename, XSH_SPECTRUM1D_DATA_BPP,
    s->flux_header, CPL_IO_DEFAULT),
    "Could not save data to %s extension 0", filename);
  check_msg (cpl_image_save ( s->errs, filename, XSH_SPECTRUM1D_ERRS_BPP,
    s->errs_header, CPL_IO_EXTEND),
    "Could not save errs to %s extension 1", filename);
  check_msg (cpl_image_save ( s->qual, filename, XSH_SPECTRUM1D_QUAL_BPP,
    s->qual_header, CPL_IO_EXTEND),
    "Could not save qual to %s extension 2", filename);


  check(product_frame=xsh_frame_product(filename,
				 "TAG",
				 CPL_FRAME_TYPE_IMAGE,
				 CPL_FRAME_GROUP_PRODUCT,
				 CPL_FRAME_LEVEL_FINAL));

cleanup:
  if (cpl_error_get_code () != CPL_ERROR_NONE) {
    xsh_free_frame(&product_frame);
    product_frame = NULL;
  }
  return product_frame;
}
