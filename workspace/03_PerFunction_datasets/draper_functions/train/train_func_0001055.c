send_endorser(struct fujitsu *s)
{
  SANE_Status ret = SANE_STATUS_GOOD;

  unsigned char cmd[SEND_len];
  size_t cmdLen = SEND_len;

  size_t strLen = strlen(s->u_endorser_string);

  unsigned char out[S_e_data_max_len];
  size_t outLen = S_e_data_min_len + strLen;

  DBG (10, "send_endorser: start\n");

  if (!s->has_endorser_f && !s->has_endorser_b){
    DBG (10, "send_endorser: unsupported\n");
    return ret;
  }


  memset(out,0,outLen);


  if(s->u_endorser_side == ED_front){
    set_S_endorser_data_id(out,0x80);
  }
  else{
    set_S_endorser_data_id(out,0);
  }

  set_S_endorser_stamp(out,0);
  set_S_endorser_elec(out,0);

  if(s->u_endorser_step < 0){
    set_S_endorser_decr(out,S_e_decr_dec);
  }
  else{
    set_S_endorser_decr(out,S_e_decr_inc);
  }

  if(s->u_endorser_bits == 24){
    set_S_endorser_lap24(out,S_e_lap_24bit);
  }
  else{
    set_S_endorser_lap24(out,S_e_lap_16bit);
  }

  set_S_endorser_ctstep(out,abs(s->u_endorser_step));
  set_S_endorser_ulx(out,0);
  set_S_endorser_uly(out,s->u_endorser_y);

  switch (s->u_endorser_font) {
    case FONT_H:
      set_S_endorser_font(out,S_e_font_horiz);
      set_S_endorser_bold(out,0);
      break;
    case FONT_HB:
      set_S_endorser_font(out,S_e_font_horiz);
      set_S_endorser_bold(out,1);
      break;
    case FONT_HN:
      set_S_endorser_font(out,S_e_font_horiz_narrow);
      set_S_endorser_bold(out,0);
      break;
    case FONT_V:
      set_S_endorser_font(out,S_e_font_vert);
      set_S_endorser_bold(out,0);
      break;
    case FONT_VB:
      set_S_endorser_font(out,S_e_font_vert);
      set_S_endorser_bold(out,1);
      break;
  }

  set_S_endorser_size(out,0);
  set_S_endorser_revs(out,0);

  if(s->u_endorser_dir == DIR_BTT){
    set_S_endorser_dirs(out,S_e_dir_bottom_top);
  }
  else{
    set_S_endorser_dirs(out,S_e_dir_top_bottom);
  }

  set_S_endorser_string_length(out, strLen);
  set_S_endorser_string(out, s->u_endorser_string, strLen);


  memset(cmd,0,cmdLen);
  set_SCSI_opcode(cmd, SEND_code);
  set_S_xfer_datatype (cmd, S_datatype_endorser_data);
  set_S_xfer_length (cmd, outLen);

  ret = do_cmd (
      s, 1, 0,
      cmd, cmdLen,
      out, outLen,
      NULL, NULL
  );

  DBG (10, "send_endorser: finish %d\n", ret);

  return ret;
}
