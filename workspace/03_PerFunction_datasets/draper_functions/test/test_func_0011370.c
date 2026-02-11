stop_scan (Ma1509_Scanner * s)
{
  SANE_Byte cmd[8];
  SANE_Status status;

  DBG (4, "stop_scan\n");
  memset (cmd, 0, 8);

  cmd[0] = 0x1b;
  cmd[1] = 0x01;
  cmd[2] = 0x00;

  status = ma1509_cmd (s, cmd, NULL, NULL);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (1, "stop_scan: ma1509_cmd failed: %s\n", sane_strstatus (status));
      return status;
    }

  DBG (4, "stop_scan: scan stopped\n");
  return status;
}
