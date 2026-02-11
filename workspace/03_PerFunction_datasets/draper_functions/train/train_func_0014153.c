finish_pass_gather_phuff (j_compress_ptr cinfo)
{
  phuff_entropy_ptr entropy = (phuff_entropy_ptr) cinfo->entropy;
  boolean is_DC_band;
  int ci, tbl;
  jpeg_component_info * compptr;
  JHUFF_TBL **htblptr;
  boolean did[NUM_HUFF_TBLS];


  emit_eobrun(entropy);

  is_DC_band = (cinfo->Ss == 0);


  MEMZERO(did, SIZEOF(did));

  for (ci = 0; ci < cinfo->comps_in_scan; ci++) {
    compptr = cinfo->cur_comp_info[ci];
    if (is_DC_band) {
      if (cinfo->Ah != 0)
	continue;
      tbl = compptr->dc_tbl_no;
    } else {
      tbl = compptr->ac_tbl_no;
    }
    if (! did[tbl]) {
      if (is_DC_band)
        htblptr = & cinfo->dc_huff_tbl_ptrs[tbl];
      else
        htblptr = & cinfo->ac_huff_tbl_ptrs[tbl];
      if (*htblptr == NULL)
        *htblptr = jpeg_alloc_huff_table((j_common_ptr) cinfo);
      jpeg_gen_optimal_table(cinfo, *htblptr, entropy->count_ptrs[tbl]);
      did[tbl] = TRUE;
    }
  }
}
