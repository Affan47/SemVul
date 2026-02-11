read_panel(struct scanner *s,SANE_Int option)
{
  SANE_Status ret=SANE_STATUS_GOOD;

  unsigned char cmd[READ_len];
  size_t cmdLen = READ_len;

  unsigned char in[R_PANEL_len];
  size_t inLen = R_PANEL_len;

  DBG (10, "read_panel: start\n");


  if (s->hw_read[option-OPT_START]) {

    DBG (15, "read_panel: running\n");

    memset(cmd,0,cmdLen);
    set_SCSI_opcode(cmd, READ_code);
    set_R_datatype_code (cmd, SR_datatype_panel);
    set_R_xfer_length (cmd, inLen);

    ret = do_cmd (
      s, 1, 0,
      cmd, cmdLen,
      NULL, 0,
      in, &inLen
    );

    if (ret == SANE_STATUS_GOOD || ret == SANE_STATUS_EOF) {

      memset(s->hw_read,0,sizeof(s->hw_read));

      s->panel_start = get_R_PANEL_start(in);
      s->panel_stop = get_R_PANEL_stop(in);
      s->panel_butt3 = get_R_PANEL_butt3(in);
      s->panel_new_file = get_R_PANEL_new_file(in);
      s->panel_count_only = get_R_PANEL_count_only(in);
      s->panel_bypass_mode = get_R_PANEL_bypass_mode(in);
      s->panel_enable_led = get_R_PANEL_enable_led(in);
      s->panel_counter = get_R_PANEL_counter(in);
      ret = SANE_STATUS_GOOD;
    }
  }

  s->hw_read[option-OPT_START] = 1;

  DBG (10, "read_panel: finish %d\n",s->panel_counter);

  return ret;
}
