start_scan (struct scanner *s, int type)
{
  SANE_Status ret = SANE_STATUS_GOOD;

  unsigned char cmd[SCAN_len];
  size_t cmdLen = SCAN_len;

  unsigned char out[] = {WD_wid_front, WD_wid_back};
  size_t outLen = 2;

  DBG (10, "start_scan: start\n");


  if(type){
    out[0] = type;
    out[1] = type;
  }

  if (s->s.source != SOURCE_ADF_DUPLEX) {
    outLen--;
    if(s->s.source == SOURCE_ADF_BACK) {
      out[0] = WD_wid_back;
    }
  }

  memset(cmd,0,cmdLen);
  set_SCSI_opcode(cmd, SCAN_code);
  set_SC_xfer_length (cmd, outLen);

  ret = do_cmd (
    s, 1, 0,
    cmd, cmdLen,
    out, outLen,
    NULL, NULL
  );

  DBG (10, "start_scan: finish\n");

  return ret;
}
