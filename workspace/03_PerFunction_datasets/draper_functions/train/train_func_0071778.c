set_off_mode(struct fujitsu *s)
{
  SANE_Status ret = SANE_STATUS_GOOD;

  unsigned char cmd[SEND_DIAGNOSTIC_len];
  size_t cmdLen = SEND_DIAGNOSTIC_len;

  unsigned char out[SD_powoff_len];
  size_t outLen = SD_powoff_len;

  DBG (10, "set_off_mode: start\n");

  if (!s->has_cmd_sdiag || !s->has_cmd_rdiag || !s->has_off_mode){
    DBG (5, "set_off_mode: not supported, returning\n");
    return ret;
  }

  memset(cmd,0,cmdLen);
  set_SCSI_opcode(cmd, SEND_DIAGNOSTIC_code);
  set_SD_slftst(cmd, 0);
  set_SD_xferlen(cmd, outLen);

  memcpy(out,SD_powoff_string,SD_powoff_stringlen);
  set_SD_powoff_disable(out,!s->off_time);
  set_SD_powoff_interval(out,s->off_time/15);

  ret = do_cmd (
    s, 1, 0,
    cmd, cmdLen,
    out, outLen,
    NULL, NULL
  );

  if (ret != SANE_STATUS_GOOD){
    DBG (5, "set_off_mode: send diag error: %d\n", ret);
    return ret;
  }

  DBG (10, "set_off_mode: finish\n");

  return SANE_STATUS_GOOD;
}
