decode_mcu_DC_refine (j_decompress_ptr cinfo, JBLOCKROW *MCU_data)
{
  huff_entropy_ptr entropy = (huff_entropy_ptr) cinfo->entropy;
  int p1, blkn;
  BITREAD_STATE_VARS;


  if (cinfo->restart_interval) {
    if (entropy->restarts_to_go == 0)
      if (! process_restart(cinfo))
	return FALSE;
  }


  BITREAD_LOAD_STATE(cinfo,entropy->bitstate);

  p1 = 1 << cinfo->Al;


  for (blkn = 0; blkn < cinfo->blocks_in_MCU; blkn++) {

    CHECK_BIT_BUFFER(br_state, 1, return FALSE);
    if (GET_BITS(1))
      MCU_data[blkn][0][0] |= p1;

  }


  BITREAD_SAVE_STATE(cinfo,entropy->bitstate);


  entropy->restarts_to_go--;

  return TRUE;
}
