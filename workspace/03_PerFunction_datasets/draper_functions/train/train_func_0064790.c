endorser(struct fujitsu *s)
{
  SANE_Status ret = SANE_STATUS_GOOD;

  unsigned char cmd[ENDORSER_len];
  size_t cmdLen = ENDORSER_len;

  unsigned char out[ED_max_len];
  size_t outLen = ED_max_len;

  DBG (10, "endorser: start\n");

  memset(cmd,0,cmdLen);
  set_SCSI_opcode(cmd, ENDORSER_code);

  memset(out,0,outLen);

  if (s->has_endorser_f || s->has_endorser_b){


    if(s->u_endorser_side == ED_front){
      set_ED_endorser_data_id(out,0x80);
    }
    else{
      set_ED_endorser_data_id(out,0);
    }

    if(s->u_endorser){
      set_ED_stop(out,ED_start);
    }
    else{
      set_ED_stop(out,ED_stop);
    }

    set_ED_side(out,s->u_endorser_side);

    if(s->u_endorser_bits == 24){
      set_ED_lap24(out,ED_lap_24bit);
      set_ED_initial_count_24(out,s->u_endorser_val);
    }

    else{
      outLen = ED_min_len;
      set_ED_lap24(out,ED_lap_16bit);
      set_ED_initial_count_16(out,s->u_endorser_val);
    }

    set_E_xferlen(cmd, outLen);
    ret = do_cmd (
      s, 1, 0,
      cmd, cmdLen,
      out, outLen,
      NULL, NULL
    );
  }

  DBG (10, "endorser: finish %d\n", ret);

  return ret;
}
