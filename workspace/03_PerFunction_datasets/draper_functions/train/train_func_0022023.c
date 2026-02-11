jpeg_calc_trans_dimensions (j_compress_ptr cinfo)
{
  if (cinfo->min_DCT_h_scaled_size < 1 || cinfo->min_DCT_h_scaled_size > 16
      || cinfo->min_DCT_h_scaled_size != cinfo->min_DCT_v_scaled_size)
    ERREXIT2(cinfo, JERR_BAD_DCTSIZE,
	     cinfo->min_DCT_h_scaled_size, cinfo->min_DCT_v_scaled_size);

  cinfo->block_size = cinfo->min_DCT_h_scaled_size;

  switch (cinfo->block_size) {
  case 2: cinfo->natural_order = jpeg_natural_order2; break;
  case 3: cinfo->natural_order = jpeg_natural_order3; break;
  case 4: cinfo->natural_order = jpeg_natural_order4; break;
  case 5: cinfo->natural_order = jpeg_natural_order5; break;
  case 6: cinfo->natural_order = jpeg_natural_order6; break;
  case 7: cinfo->natural_order = jpeg_natural_order7; break;
  default: cinfo->natural_order = jpeg_natural_order; break;
  }

  cinfo->lim_Se = cinfo->block_size < DCTSIZE ?
    cinfo->block_size * cinfo->block_size - 1 : DCTSIZE2-1;
}
