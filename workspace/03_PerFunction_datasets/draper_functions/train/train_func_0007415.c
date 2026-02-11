jinit_c_main_controller (j_compress_ptr cinfo, boolean need_full_buffer)
{
  my_main_ptr mainp;
  int ci;
  jpeg_component_info *compptr;

  mainp = (my_main_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_main_controller));
  cinfo->main = &mainp->pub;
  mainp->pub.start_pass = start_pass_main;


  if (cinfo->raw_data_in)
    return;


  if (need_full_buffer) {
#ifdef FULL_MAIN_BUFFER_SUPPORTED


    for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
	 ci++, compptr++) {
      mainp->whole_image[ci] = (*cinfo->mem->request_virt_sarray)
	((j_common_ptr) cinfo, JPOOL_IMAGE, FALSE,
	 compptr->width_in_blocks * ((JDIMENSION) compptr->DCT_h_scaled_size),
	 ((JDIMENSION) jround_up((long) compptr->height_in_blocks,
				 (long) compptr->v_samp_factor)) *
	 ((JDIMENSION) cinfo->min_DCT_v_scaled_size),
	 (JDIMENSION) (compptr->v_samp_factor * compptr->DCT_v_scaled_size));
    }
#else
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
#endif
  } else {
#ifdef FULL_MAIN_BUFFER_SUPPORTED
    mainp->whole_image[0] = NULL;
#endif

    for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
	 ci++, compptr++) {
      mainp->buffer[ci] = (*cinfo->mem->alloc_sarray)
	((j_common_ptr) cinfo, JPOOL_IMAGE,
	 compptr->width_in_blocks * ((JDIMENSION) compptr->DCT_h_scaled_size),
	 (JDIMENSION) (compptr->v_samp_factor * compptr->DCT_v_scaled_size));
    }
  }
}
