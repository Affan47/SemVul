jinit_huff_decoder (j_decompress_ptr cinfo)
{
  huff_entropy_ptr entropy;
  int i;

  entropy = (huff_entropy_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(huff_entropy_decoder));
  cinfo->entropy = &entropy->pub;
  entropy->pub.start_pass = start_pass_huff_decoder;
  entropy->pub.finish_pass = finish_pass_huff;

  if (cinfo->progressive_mode) {

    int *coef_bit_ptr, ci;
    cinfo->coef_bits = (int (*)[DCTSIZE2])
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  cinfo->num_components*DCTSIZE2*SIZEOF(int));
    coef_bit_ptr = & cinfo->coef_bits[0][0];
    for (ci = 0; ci < cinfo->num_components; ci++)
      for (i = 0; i < DCTSIZE2; i++)
	*coef_bit_ptr++ = -1;


    for (i = 0; i < NUM_HUFF_TBLS; i++) {
      entropy->derived_tbls[i] = NULL;
    }
  } else {

    for (i = 0; i < NUM_HUFF_TBLS; i++) {
      entropy->dc_derived_tbls[i] = entropy->ac_derived_tbls[i] = NULL;
    }
  }
}
