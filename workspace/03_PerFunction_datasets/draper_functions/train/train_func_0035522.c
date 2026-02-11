openexif_jpeg_add_quant_table (oe_j_compress_ptr cinfo, int which_tbl,
		      const unsigned int *basic_table,
		      int scale_factor, boolean force_baseline)


{
  OE_JQUANT_TBL ** qtblptr;
  int i;
  long temp;


  if (cinfo->global_state != CSTATE_START)
    ERREXIT1(cinfo, OE_JERR_BAD_STATE, cinfo->global_state);

  if (which_tbl < 0 || which_tbl >= NUM_QUANT_TBLS)
    ERREXIT1(cinfo, OE_JERR_DQT_INDEX, which_tbl);

  qtblptr = & cinfo->quant_tbl_ptrs[which_tbl];

  if (*qtblptr == NULL)
    *qtblptr = openexif_jpeg_alloc_quant_table((oe_j_common_ptr) cinfo);

  for (i = 0; i < DCTSIZE2; i++) {
    temp = ((long) basic_table[i] * scale_factor + 50L) / 100L;

    if (temp <= 0L) temp = 1L;
    if (temp > 32767L) temp = 32767L;
    if (force_baseline && temp > 255L)
      temp = 255L;
    (*qtblptr)->quantval[i] = (UINT16) temp;
  }


  (*qtblptr)->sent_table = FALSE;
}
