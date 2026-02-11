emit_dac (j_compress_ptr cinfo)


{
#ifdef C_ARITH_CODING_SUPPORTED
  char dc_in_use[NUM_ARITH_TBLS];
  char ac_in_use[NUM_ARITH_TBLS];
  int length, i;
  jpeg_component_info *compptr;

  for (i = 0; i < NUM_ARITH_TBLS; i++)
    dc_in_use[i] = ac_in_use[i] = 0;

  for (i = 0; i < cinfo->comps_in_scan; i++) {
    compptr = cinfo->cur_comp_info[i];

    if (cinfo->Ss == 0 && cinfo->Ah == 0)
      dc_in_use[compptr->dc_tbl_no] = 1;

    if (cinfo->Se)
      ac_in_use[compptr->ac_tbl_no] = 1;
  }

  length = 0;
  for (i = 0; i < NUM_ARITH_TBLS; i++)
    length += dc_in_use[i] + ac_in_use[i];

  emit_marker(cinfo, M_DAC);

  emit_2bytes(cinfo, length*2 + 2);

  for (i = 0; i < NUM_ARITH_TBLS; i++) {
    if (dc_in_use[i]) {
      emit_byte(cinfo, i);
      emit_byte(cinfo, cinfo->arith_dc_L[i] + (cinfo->arith_dc_U[i]<<4));
    }
    if (ac_in_use[i]) {
      emit_byte(cinfo, i + 0x10);
      emit_byte(cinfo, cinfo->arith_ac_K[i]);
    }
  }
#endif
}
