object_position (struct fujitsu *s, int i_load)
{
  SANE_Status ret = SANE_STATUS_GOOD;

  unsigned char cmd[OBJECT_POSITION_len];
  size_t cmdLen = OBJECT_POSITION_len;

  DBG (10, "object_position: start\n");

  if (s->source == SOURCE_FLATBED) {
    DBG (10, "object_position: flatbed no-op\n");
    return SANE_STATUS_GOOD;
  }

  memset(cmd,0,cmdLen);
  set_SCSI_opcode(cmd, OBJECT_POSITION_code);

  if (i_load) {
    DBG (15, "object_position: load\n");
    set_OP_autofeed (cmd, OP_Feed);
  }
  else {
    DBG (15, "object_position: eject\n");
    set_OP_autofeed (cmd, OP_Discharge);
  }

  ret = do_cmd (
    s, 1, 0,
    cmd, cmdLen,
    NULL, 0,
    NULL, NULL
  );
  if (ret != SANE_STATUS_GOOD)
    return ret;

  wait_scanner (s);

  DBG (10, "object_position: finish\n");

  return ret;
}
