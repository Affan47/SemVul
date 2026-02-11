do_flip_v (j_decompress_ptr srcinfo, j_compress_ptr dstinfo,
	   jvirt_barray_ptr *src_coef_arrays,
	   jvirt_barray_ptr *dst_coef_arrays)

{
  JDIMENSION MCU_rows, comp_height, dst_blk_x, dst_blk_y;
  int ci, i, j, offset_y;
  JBLOCKARRAY src_buffer, dst_buffer;
  JBLOCKROW src_row_ptr, dst_row_ptr;
  JCOEFPTR src_ptr, dst_ptr;
  jpeg_component_info *compptr;


  MCU_rows = dstinfo->image_height / (dstinfo->max_v_samp_factor * DCTSIZE);

  for (ci = 0; ci < dstinfo->num_components; ci++) {
    compptr = dstinfo->comp_info + ci;
    comp_height = MCU_rows * compptr->v_samp_factor;
    for (dst_blk_y = 0; dst_blk_y < compptr->height_in_blocks;
	 dst_blk_y += compptr->v_samp_factor) {
      dst_buffer = (*srcinfo->mem->access_virt_barray)
	((j_common_ptr) srcinfo, dst_coef_arrays[ci], dst_blk_y,
	 (JDIMENSION) compptr->v_samp_factor, TRUE);
      if (dst_blk_y < comp_height) {

	src_buffer = (*srcinfo->mem->access_virt_barray)
	  ((j_common_ptr) srcinfo, src_coef_arrays[ci],
	   comp_height - dst_blk_y - (JDIMENSION) compptr->v_samp_factor,
	   (JDIMENSION) compptr->v_samp_factor, FALSE);
      } else {

	src_buffer = (*srcinfo->mem->access_virt_barray)
	  ((j_common_ptr) srcinfo, src_coef_arrays[ci], dst_blk_y,
	   (JDIMENSION) compptr->v_samp_factor, FALSE);
      }
      for (offset_y = 0; offset_y < compptr->v_samp_factor; offset_y++) {
	if (dst_blk_y < comp_height) {

	  dst_row_ptr = dst_buffer[offset_y];
	  src_row_ptr = src_buffer[compptr->v_samp_factor - offset_y - 1];
	  for (dst_blk_x = 0; dst_blk_x < compptr->width_in_blocks;
	       dst_blk_x++) {
	    dst_ptr = dst_row_ptr[dst_blk_x];
	    src_ptr = src_row_ptr[dst_blk_x];
	    for (i = 0; i < DCTSIZE; i += 2) {

	      for (j = 0; j < DCTSIZE; j++)
		*dst_ptr++ = *src_ptr++;

	      for (j = 0; j < DCTSIZE; j++)
		*dst_ptr++ = - *src_ptr++;
	    }
	  }
	} else {

	  jcopy_block_row(src_buffer[offset_y], dst_buffer[offset_y],
			  compptr->width_in_blocks);
	}
      }
    }
  }
}
