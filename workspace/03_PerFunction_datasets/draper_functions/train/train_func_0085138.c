compress_data (j_compress_ptr cinfo, JSAMPIMAGE input_buf)
{
  j_lossy_c_ptr lossyc = (j_lossy_c_ptr) cinfo->codec;
  c_coef_ptr coef = (c_coef_ptr) lossyc->coef_private;
  JDIMENSION MCU_col_num;
  JDIMENSION last_MCU_col = cinfo->MCUs_per_row - 1;
  JDIMENSION last_iMCU_row = cinfo->total_iMCU_rows - 1;
  int blkn, bi, ci, yindex, yoffset, blockcnt;
  JDIMENSION ypos, xpos;
  jpeg_component_info *compptr;


  for (yoffset = coef->MCU_vert_offset; yoffset < coef->MCU_rows_per_iMCU_row;
       yoffset++) {
    for (MCU_col_num = coef->mcu_ctr; MCU_col_num <= last_MCU_col;
	 MCU_col_num++) {


      blkn = 0;
      for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
	compptr = cinfo->cur_comp_info[ci];
	blockcnt = (MCU_col_num < last_MCU_col) ? compptr->MCU_width
						: compptr->last_col_width;
	xpos = MCU_col_num * compptr->MCU_sample_width;
	ypos = yoffset * DCTSIZE;
	for (yindex = 0; yindex < compptr->MCU_height; yindex++) {
	  if (coef->iMCU_row_num < last_iMCU_row ||
	      yoffset+yindex < compptr->last_row_height) {
	    (*lossyc->fdct_forward_DCT) (cinfo, compptr,
				    input_buf[compptr->component_index],
				    coef->MCU_buffer[blkn],
				    ypos, xpos, (JDIMENSION) blockcnt);
	    if (blockcnt < compptr->MCU_width) {

	      jzero_far((void FAR *) coef->MCU_buffer[blkn + blockcnt],
			(compptr->MCU_width - blockcnt) * SIZEOF(JBLOCK));
	      for (bi = blockcnt; bi < compptr->MCU_width; bi++) {
		coef->MCU_buffer[blkn+bi][0][0] = coef->MCU_buffer[blkn+bi-1][0][0];
	      }
	    }
	  } else {

	    jzero_far((void FAR *) coef->MCU_buffer[blkn],
		      compptr->MCU_width * SIZEOF(JBLOCK));
	    for (bi = 0; bi < compptr->MCU_width; bi++) {
	      coef->MCU_buffer[blkn+bi][0][0] = coef->MCU_buffer[blkn-1][0][0];
	    }
	  }
	  blkn += compptr->MCU_width;
	  ypos += DCTSIZE;
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
