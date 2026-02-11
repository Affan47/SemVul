compress_output (j_compress_ptr cinfo, JSAMPIMAGE input_buf)
{
  j_lossy_c_ptr lossyc = (j_lossy_c_ptr) cinfo->codec;
  c_coef_ptr coef = (c_coef_ptr) lossyc->coef_private;
  JDIMENSION MCU_col_num;
  int blkn, ci, xindex, yindex, yoffset;
  JDIMENSION start_col;
  JBLOCKARRAY buffer[MAX_COMPS_IN_SCAN];
  JBLOCKROW buffer_ptr;
  jpeg_component_info *compptr;
  (void)input_buf;


  for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
    compptr = cinfo->cur_comp_info[ci];
    buffer[ci] = (*cinfo->mem->access_virt_barray)
      ((j_common_ptr) cinfo, coef->whole_image[compptr->component_index],
       coef->iMCU_row_num * compptr->v_samp_factor,
       (JDIMENSION) compptr->v_samp_factor, FALSE);
  }


  for (yoffset = coef->MCU_vert_offset; yoffset < coef->MCU_rows_per_iMCU_row;
       yoffset++) {
    for (MCU_col_num = coef->mcu_ctr; MCU_col_num < cinfo->MCUs_per_row;
	 MCU_col_num++) {

      blkn = 0;
      for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
	compptr = cinfo->cur_comp_info[ci];
	start_col = MCU_col_num * compptr->MCU_width;
	for (yindex = 0; yindex < compptr->MCU_height; yindex++) {
	  buffer_ptr = buffer[ci][yindex+yoffset] + start_col;
	  for (xindex = 0; xindex < compptr->MCU_width; xindex++) {
	    coef->MCU_buffer[blkn++] = buffer_ptr++;
	  }
	}
      }

      if (! (*lossyc->entropy_encode_mcu) (cinfo, coef->MCU_buffer)) {

	coef->MCU_vert_offset = yoffset;
	coef->mcu_ctr = MCU_col_num;
	return FALSE;
      }
    }

    coef->mcu_ctr = 0;
  }

  coef->iMCU_row_num++;
  start_iMCU_row(cinfo);
  return TRUE;
}
