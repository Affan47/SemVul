compress_output (j_compress_ptr cinfo, JSAMPIMAGE input_buf)
{
  j_lossless_c_ptr losslsc = (j_lossless_c_ptr) cinfo->codec;
  c_diff_ptr diff = (c_diff_ptr) losslsc->diff_private;


  int comp, ci  ;
  JSAMPARRAY buffer[MAX_COMPONENTS];
  jpeg_component_info *compptr;
  (void)input_buf;


  for (comp = 0; comp < cinfo->comps_in_scan; comp++) {
    compptr = cinfo->cur_comp_info[comp];
    ci = compptr->component_index;
    buffer[ci] = (*cinfo->mem->access_virt_sarray)
      ((j_common_ptr) cinfo, diff->whole_image[ci],
       diff->iMCU_row_num * compptr->v_samp_factor,
       (JDIMENSION) compptr->v_samp_factor, FALSE);
  }

  return compress_data(cinfo, buffer);
}
