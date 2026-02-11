do_crop (j_decompress_ptr srcinfo, j_compress_ptr dstinfo,
	 JDIMENSION x_crop_offset, JDIMENSION y_crop_offset,
	 jvirt_barray_ptr *src_coef_arrays,
	 jvirt_barray_ptr *dst_coef_arrays)

{
  JDIMENSION dst_blk_y, x_crop_blocks, y_crop_blocks;
  int ci, offset_y;
  JBLOCKARRAY src_buffer, dst_buffer;
  jpeg_component_info *compptr;


  for (ci = 0; ci < dstinfo->num_components; ci++) {
    compptr = dstinfo->comp_info + ci;
    x_crop_blocks = x_crop_offset * compptr->h_samp_factor;
    y_crop_blocks = y_crop_offset * compptr->v_samp_factor;
    for (dst_blk_y = 0; dst_blk_y < compptr->height_in_blocks;
	 dst_blk_y += compptr->v_samp_factor) {
      dst_buffer = (*srcinfo->mem->access_virt_barray)
	((j_common_ptr) srcinfo, dst_coef_arrays[ci], dst_blk_y,
	 (JDIMENSION) compptr->v_samp_factor, TRUE);
      src_buffer = (*srcinfo->mem->access_virt_barray)
	((j_common_ptr) srcinfo, src_coef_arrays[ci],
	 dst_blk_y + y_crop_blocks,
	 (JDIMENSION) compptr->v_samp_factor, FALSE);
      for (offset_y = 0; offset_y < compptr->v_samp_factor; offset_y++) {
	jcopy_block_row(src_buffer[offset_y] + x_crop_blocks,
			dst_buffer[offset_y],
			compptr->width_in_blocks);
      }
    }
  }
}
