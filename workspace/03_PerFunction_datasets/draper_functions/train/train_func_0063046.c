finish_pass_gather (j_compress_ptr cinfo)
{
  huff_entropy_ptr entropy = (huff_entropy_ptr) cinfo->entropy;
  int ci, tbl;
  jpeg_component_info * compptr;
  JHUFF_TBL **htblptr;
  boolean did_dc[NUM_HUFF_TBLS];
  boolean did_ac[NUM_HUFF_TBLS];


  if (cinfo->progressive_mode)

    emit_eobrun(entropy);

  MEMZERO(did_dc, SIZEOF(did_dc));
  MEMZERO(did_ac, SIZEOF(did_ac));

  for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
    compptr = cinfo->cur_comp_info[ci];

    if (cinfo->Ss == 0 && cinfo->Ah == 0) {
      tbl = compptr->dc_tbl_no;
      if (! did_dc[tbl]) {
	htblptr = & cinfo->dc_huff_tbl_ptrs[tbl];
	if (*htblptr == NULL)
	  *htblptr = jpeg_alloc_huff_table((j_common_ptr) cinfo);
	jpeg_gen_optimal_table(cinfo, *htblptr, entropy->dc_count_ptrs[tbl]);
	did_dc[tbl] = TRUE;
      }
    }

    if (cinfo->Se) {
      tbl = compptr->ac_tbl_no;
      if (! did_ac[tbl]) {
	htblptr = & cinfo->ac_huff_tbl_ptrs[tbl];
	if (*htblptr == NULL)
	  *htblptr = jpeg_alloc_huff_table((j_common_ptr) cinfo);
	jpeg_gen_optimal_table(cinfo, *htblptr, entropy->ac_count_ptrs[tbl]);
	did_ac[tbl] = TRUE;
      }
    }
  }
}
