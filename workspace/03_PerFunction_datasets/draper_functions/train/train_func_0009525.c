do_wipe (j_decompress_ptr srcinfo, j_compress_ptr dstinfo,
	 JDIMENSION x_crop_offset, JDIMENSION y_crop_offset,
	 jvirt_barray_ptr *src_coef_arrays,
	 JDIMENSION drop_width, JDIMENSION drop_height)

{
  JDIMENSION comp_width, comp_height;
  JDIMENSION blk_y, x_wipe_blocks, y_wipe_blocks;
  int ci, offset_y;
  JBLOCKARRAY buffer;
  jpeg_component_info *compptr;

  for (ci = 0; ci < dstinfo->num_components; ci++) {
    compptr = dstinfo->comp_info + ci;
    comp_width = drop_width * compptr->h_samp_factor;
    comp_height = drop_height * compptr->v_samp_factor;
    x_wipe_blocks = x_crop_offset * compptr->h_samp_factor;
    y_wipe_blocks = y_crop_offset * compptr->v_samp_factor;
    for (blk_y = 0; blk_y < comp_height; blk_y += compptr->v_samp_factor) {
      buffer = (*srcinfo->mem->access_virt_barray)
	((j_common_ptr) srcinfo, src_coef_arrays[ci], blk_y + y_wipe_blocks,
	 (JDIMENSION) compptr->v_samp_factor, TRUE);
      for (offset_y = 0; offset_y < compptr->v_samp_factor; offset_y++) {
	FMEMZERO(buffer[offset_y] + x_wipe_blocks,
		 comp_width * SIZEOF(JBLOCK));
      }
    }
  }
}
