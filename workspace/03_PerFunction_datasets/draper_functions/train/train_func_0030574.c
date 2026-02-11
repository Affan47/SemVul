emit_restart (phuff_entropy_ptr entropy, int restart_num)
{
  int ci;

  emit_eobrun(entropy);

  if (! entropy->gather_statistics) {
    flush_bits(entropy);
    emit_byte(entropy, 0xFF);
    emit_byte(entropy, JPEG_RST0 + restart_num);
  }

  if (entropy->cinfo->Ss == 0) {

    for (ci = 0; ci < entropy->cinfo->comps_in_scan; ci++)
      entropy->last_dc_val[ci] = 0;
  } else {

    entropy->EOBRUN = 0;
    entropy->BE = 0;
  }
}
