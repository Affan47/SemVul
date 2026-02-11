encode_mcu_DC_refine (j_compress_ptr cinfo, JBLOCKROW *MCU_data)
{
  j_lossy_c_ptr lossyc = (j_lossy_c_ptr) cinfo->codec;
  phuff_entropy_ptr entropy = (phuff_entropy_ptr) lossyc->entropy_private;
  register int temp;
  int blkn;
  int Al = cinfo->Al;
  JBLOCKROW block;

  entropy->next_output_byte = cinfo->dest->next_output_byte;
  entropy->free_in_buffer = cinfo->dest->free_in_buffer;


  if (cinfo->restart_interval)
    if (entropy->restarts_to_go == 0)
      emit_restart(entropy, entropy->next_restart_num);


  for (blkn = 0; blkn < cinfo->data_units_in_MCU; blkn++) {
    block = MCU_data[blkn];


    temp = (*block)[0];
    emit_bits(entropy, (unsigned int) (temp >> Al), 1);
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
