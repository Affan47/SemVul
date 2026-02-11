encode_mcu_AC_first (j_compress_ptr cinfo, JBLOCKROW *MCU_data)
{
  j_lossy_c_ptr lossyc = (j_lossy_c_ptr) cinfo->codec;
  phuff_entropy_ptr entropy = (phuff_entropy_ptr) lossyc->entropy_private;
  register int temp, temp2;
  register int nbits;
  register int r, k;
  int Se = cinfo->Se;
  int Al = cinfo->Al;
  JBLOCKROW block;

  entropy->next_output_byte = cinfo->dest->next_output_byte;
  entropy->free_in_buffer = cinfo->dest->free_in_buffer;


  if (cinfo->restart_interval)
    if (entropy->restarts_to_go == 0)
      emit_restart(entropy, entropy->next_restart_num);


  block = MCU_data[0];


  r = 0;

  for (k = cinfo->Ss; k <= Se; k++) {
    if ((temp = (*block)[jpeg_natural_order[k]]) == 0) {
      r++;
      continue;
    }


    if (temp < 0) {
      temp = -temp;
      temp >>= Al;

      temp2 = ~temp;
    } else {
      temp >>= Al;
      temp2 = temp;
    }

    if (temp == 0) {
      r++;
      continue;
    }


    if (entropy->EOBRUN > 0)
      emit_eobrun(entropy);

    while (r > 15) {
      emit_symbol(entropy, entropy->ac_tbl_no, 0xF0);
      r -= 16;
    }


    nbits = 1;
    while ((temp >>= 1))
      nbits++;

    if (nbits > MAX_COEF_BITS)
      ERREXIT(cinfo, JERR_BAD_DCT_COEF);


    emit_symbol(entropy, entropy->ac_tbl_no, (r << 4) + nbits);


    emit_bits(entropy, (unsigned int) temp2, nbits);

    r = 0;
  }

  if (r > 0) {
    entropy->EOBRUN++;
    if (entropy->EOBRUN == 0x7FFF)
      emit_eobrun(entropy);
  }

  cinfo->dest->next_output_byte = entropy->next_output_byte;
  cinfo->dest->free_in_buffer = entropy->free_in_buffer;


  if (cinfo->restart_interval) {
    if (entropy->restarts_to_go == 0) {
      entropy->restarts_to_go = cinfo->restart_interval;
      entropy->next_restart_num++;
      entropy->next_restart_num &= 7;
    }
    entropy->restarts_to_go--;
  }

  return TRUE;
}
