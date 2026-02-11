init_serial (struct fujitsu *s)
{
  SANE_Status ret = SANE_STATUS_GOOD;
  unsigned int sn = 0;

  unsigned char cmd[SEND_DIAGNOSTIC_len];
  size_t cmdLen = SEND_DIAGNOSTIC_len;

  unsigned char out[SD_gdi_len];
  size_t outLen = SD_gdi_len;

  unsigned char in[RD_gdi_len];
  size_t inLen = RD_gdi_len;

  DBG (10, "init_serial: start\n");

  if (!s->has_cmd_sdiag || !s->has_cmd_rdiag || s->broken_diag_serial){
    DBG (5, "init_serial: send/read diag not supported, returning\n");
    return SANE_STATUS_INVAL;
  }

  memset(cmd,0,cmdLen);
  set_SCSI_opcode(cmd, SEND_DIAGNOSTIC_code);
  set_SD_slftst(cmd, 0);
  set_SD_xferlen(cmd, outLen);

  memcpy(out,SD_gdi_string,outLen);

  ret = do_cmd (
    s, 1, 0,
    cmd, cmdLen,
    out, outLen,
    NULL, NULL
  );

  if (ret != SANE_STATUS_GOOD){
    DBG (5, "init_serial: send diag error: %d\n", ret);
    return ret;
  }

  memset(cmd,0,cmdLen);
  set_SCSI_opcode(cmd, READ_DIAGNOSTIC_code);
  set_RD_xferlen(cmd, inLen);

  ret = do_cmd (
    s, 1, 0,
    cmd, cmdLen,
    NULL, 0,
    in, &inLen
  );

  if (ret != SANE_STATUS_GOOD){
    DBG (5, "init_serial: read diag error: %d\n", ret);
    return ret;
  }

  sn = get_RD_id_serial(in);

  DBG (15, "init_serial: found sn %d\n",sn);

  sprintf(s->serial_name, "%s:%d", s->model_name, sn);

  DBG (15, "init_serial: serial_name: %s\n",s->serial_name);

  DBG (10, "init_serial: finish\n");

  return SANE_STATUS_GOOD;
}
