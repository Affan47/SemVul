decode_mcu_AC_first (j_decompress_ptr cinfo, JBLOCKROW *MCU_data)
{
  arith_entropy_ptr entropy = (arith_entropy_ptr) cinfo->entropy;
  JBLOCKROW block;
  unsigned char *st;
  int tbl, sign, k;
  int v, m;


  if (cinfo->restart_interval) {
    if (entropy->restarts_to_go == 0)
      process_restart(cinfo);
    entropy->restarts_to_go--;
  }

  if (entropy->ct == -1) return TRUE;


  block = MCU_data[0];
  tbl = cinfo->cur_comp_info[0]->ac_tbl_no;


  for (k = cinfo->Ss; k <= cinfo->Se; k++) {
    st = entropy->ac_stats[tbl] + 3 * (k - 1);
    if (arith_decode(cinfo, st)) break;
    while (arith_decode(cinfo, st + 1) == 0) {
      st += 3; k++;
      if (k > cinfo->Se) {
	WARNMS(cinfo, JWRN_ARITH_BAD_CODE);
	entropy->ct = -1;
	return TRUE;
      }
    }


    entropy->ac_stats[tbl][245] = 0;
    sign = arith_decode(cinfo, entropy->ac_stats[tbl] + 245);
    st += 2;

    if ((m = arith_decode(cinfo, st)) != 0) {
      if (arith_decode(cinfo, st)) {
	m <<= 1;
	st = entropy->ac_stats[tbl] +
	     (k <= cinfo->arith_ac_K[tbl] ? 189 : 217);
	while (arith_decode(cinfo, st)) {
	  if ((m <<= 1) == 0x8000) {
	    WARNMS(cinfo, JWRN_ARITH_BAD_CODE);
	    entropy->ct = -1;
	    return TRUE;
	  }
	  st += 1;
	}
      }
    }
    v = m;

    st += 14;
    while (m >>= 1)
      if (arith_decode(cinfo, st)) v |= m;
    v += 1; if (sign) v = -v;

    (*block)[jpeg_natural_order[k]] = (JCOEF) (v << cinfo->Al);
  }

  return TRUE;
}
