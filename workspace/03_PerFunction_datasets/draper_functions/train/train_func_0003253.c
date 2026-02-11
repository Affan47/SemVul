decompress_data (j_decompress_ptr cinfo, JSAMPIMAGE output_buf)
{
  my_coef_ptr coef = (my_coef_ptr) cinfo->coef;
  JDIMENSION last_iMCU_row = cinfo->total_iMCU_rows - 1;
  JDIMENSION block_num;
  int ci, block_row, block_rows;
  JBLOCKARRAY buffer;
  JBLOCKROW buffer_ptr;
  JSAMPARRAY output_ptr;
  JDIMENSION output_col;
  jpeg_component_info *compptr;
  inverse_DCT_method_ptr inverse_DCT;


  while (cinfo->input_scan_number < cinfo->output_scan_number ||
	 (cinfo->input_scan_number == cinfo->output_scan_number &&
	  cinfo->input_iMCU_row <= cinfo->output_iMCU_row)) {
    if ((*cinfo->inputctl->consume_input)(cinfo) == JPEG_SUSPENDED)
      return JPEG_SUSPENDED;
  }


  for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
       ci++, compptr++) {

    if (! compptr->component_needed)
      continue;

    buffer = (*cinfo->mem->access_virt_barray)
      ((j_common_ptr) cinfo, coef->whole_image[ci],
       cinfo->tile_decode ? 0 : cinfo->output_iMCU_row * compptr->v_samp_factor,
       (JDIMENSION) compptr->v_samp_factor, FALSE);

    if (cinfo->output_iMCU_row < last_iMCU_row)
      block_rows = compptr->v_samp_factor;
    else {

      block_rows = (int) (compptr->height_in_blocks % compptr->v_samp_factor);
      if (block_rows == 0) block_rows = compptr->v_samp_factor;
    }
    inverse_DCT = cinfo->idct->inverse_DCT[ci];
    output_ptr = output_buf[ci];
    int width_in_blocks = compptr->width_in_blocks;
    int start_block = 0;
#if ANDROID_TILE_BASED_DECODE
    if (cinfo->tile_decode) {

      width_in_blocks = jmin(width_in_blocks,
        (cinfo->coef->MCU_column_right_boundary -
         cinfo->coef->MCU_column_left_boundary) *
         compptr->h_samp_factor);
      start_block = coef->pub.MCU_columns_to_skip *
         compptr->h_samp_factor;
   }
#endif

    for (block_row = 0; block_row < block_rows; block_row++) {
      buffer_ptr = buffer[block_row];
      output_col = start_block * compptr->DCT_scaled_size;
      buffer_ptr += start_block;
      for (block_num = start_block; block_num < width_in_blocks; block_num++) {
	(*inverse_DCT) (cinfo, compptr, (JCOEFPTR) buffer_ptr,
			output_ptr, output_col);
	buffer_ptr++;
	output_col += compptr->DCT_scaled_size;
      }
      output_ptr += compptr->DCT_scaled_size;
    }
  }

  if (++(cinfo->output_iMCU_row) < cinfo->total_iMCU_rows)
    return JPEG_ROW_COMPLETED;
  return JPEG_SCAN_COMPLETED;
}
