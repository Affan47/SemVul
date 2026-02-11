reject_lo_hi(cpl_image *image, double min, double max)
{
  cpl_mask *mask_lo = NULL;
  cpl_mask *mask_hi = NULL;

  mask_lo = cpl_mask_threshold_image_create(image, -DBL_MAX, min);
  mask_hi = cpl_mask_threshold_image_create(image, max, DBL_MAX);
  assure_mem( mask_lo );
  assure_mem( mask_hi );

  cpl_mask_or(mask_lo, mask_hi);

  cpl_image_reject_from_mask(image, mask_lo);

  cleanup:
  xsh_free_mask(&mask_lo);
  xsh_free_mask(&mask_hi);
  return;
}
