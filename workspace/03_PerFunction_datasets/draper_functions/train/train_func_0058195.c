transencode_master_selection (j_compress_ptr cinfo,
			      jvirt_barray_ptr * coef_arrays)
{

  jinit_c_master_control(cinfo, TRUE );


  if (cinfo->arith_code)
    jinit_arith_encoder(cinfo);
  else {
    jinit_huff_encoder(cinfo);
  }


  transencode_coef_controller(cinfo, coef_arrays);

  jinit_marker_writer(cinfo);


  (*cinfo->mem->realize_virt_arrays) ((j_common_ptr) cinfo);


  (*cinfo->marker->write_file_header) (cinfo);
}
