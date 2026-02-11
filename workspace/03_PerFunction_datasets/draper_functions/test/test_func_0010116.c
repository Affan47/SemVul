compress_first_pass (j_compress_ptr cinfo, JSAMPIMAGE input_buf)
{
  j_lossy_c_ptr lossyc = (j_lossy_c_ptr) cinfo->codec;
  c_coef_ptr coef = (c_coef_ptr) lossyc->coef_private;
  JDIMENSION last_iMCU_row = cinfo->total_iMCU_rows - 1;
  JDIMENSION blocks_across, MCUs_across, MCUindex;
  int bi, ci, h_samp_factor, block_row, block_rows, ndummy;
  JCOEF lastDC;
  jpeg_component_info *compptr;
  JBLOCKARRAY buffer;
  JBLOCKROW thisblockrow, lastblockrow;

  for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
       ci++, compptr++) {

    buffer = (*cinfo->mem->access_virt_barray)
      ((j_common_ptr) cinfo, coef->whole_image[ci],
       coef->iMCU_row_num * compptr->v_samp_factor,
       (JDIMENSION) compptr->v_samp_factor, TRUE);

    if (coef->iMCU_row_num < last_iMCU_row)
      block_rows = compptr->v_samp_factor;
    else {

      block_rows = (int) (compptr->height_in_data_units % compptr->v_samp_factor);
      if (block_rows == 0) block_rows = compptr->v_samp_factor;
    }
    blocks_across = compptr->width_in_data_units;
    h_samp_factor = compptr->h_samp_factor;

    ndummy = (int) (blocks_across % h_samp_factor);
    if (ndummy > 0)
      ndummy = h_samp_factor - ndummy;


    for (block_row = 0; block_row < block_rows; block_row++) {
      thisblockrow = buffer[block_row];
      (*lossyc->fdct_forward_DCT) (cinfo, compptr,
				   input_buf[ci], thisblockrow,
				   (JDIMENSION) (block_row * DCTSIZE),
				   (JDIMENSION) 0, blocks_across);
      if (ndummy > 0) {

	thisblockrow += blocks_across;
	jzero_far((void FAR *) thisblockrow, ndummy * SIZEOF(JBLOCK));
	lastDC = thisblockrow[-1][0];
	for (bi = 0; bi < ndummy; bi++) {
	  thisblockrow[bi][0] = lastDC;
	}
      }
    }


    if (coef->iMCU_row_num == last_iMCU_row) {
      blocks_across += ndummy;
      MCUs_across = blocks_across / h_samp_factor;
      for (block_row = block_rows; block_row < compptr->v_samp_factor;
	   block_row++) {
	thisblockrow = buffer[block_row];
	lastblockrow = buffer[block_row-1];
	jzero_far((void FAR *) thisblockrow,
		  (size_t) (blocks_across * SIZEOF(JBLOCK)));
	for (MCUindex = 0; MCUindex < MCUs_across; MCUindex++) {
	  lastDC = lastblockrow[h_samp_factor-1][0];
	  for (bi = 0; bi < h_samp_factor; bi++) {
	    thisblockrow[bi][0] = lastDC;
	  }
	  thisblockrow += h_samp_factor;
	  lastblockrow += h_samp_factor;
	}
      }
    }
  }


  return compress_output(cinfo, input_buf);
}
