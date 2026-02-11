transencode_codec (j_compress_ptr cinfo,
       jvirt_barray_ptr * coef_arrays)
{
  j_lossy_c_ptr lossyc;


  lossyc = (j_lossy_c_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
        SIZEOF(jpeg_lossy_c_codec));
  cinfo->codec = (struct jpeg_c_codec *) lossyc;


  if (cinfo->arith_code) {
#ifdef WITH_ARITHMETIC_PATCH
    jinit_arith_encoder(cinfo);
#else
    ERREXIT(cinfo, JERR_ARITH_NOTIMPL);
#endif
  } else {
    if (cinfo->process == JPROC_PROGRESSIVE) {
#ifdef C_PROGRESSIVE_SUPPORTED
      jinit_phuff_encoder(cinfo);
#else
      ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif
    } else
      jinit_shuff_encoder(cinfo);
  }


  transencode_coef_controller(cinfo, coef_arrays);


  lossyc->pub.start_pass = start_pass_coef;
  lossyc->pub.compress_data = compress_output;
}
