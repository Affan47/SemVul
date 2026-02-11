six5 (struct scanner *s)
{
  SANE_Status ret = SANE_STATUS_GOOD;

  unsigned char cmd[2];
  size_t cmdLen = sizeof(cmd);
  unsigned char stat[1];
  size_t statLen = sizeof(stat);

  DBG (10, "six5: start\n");

  cmd[0] = 0x1b;
  cmd[1] = 0x65;
  statLen = 1;

  ret = do_cmd(
    s, 0,
    cmd, cmdLen,
    NULL, 0,
    stat, &statLen
  );
  if(ret){
      DBG (5, "six5: error sending cmd\n");
      return ret;
  }
  if(stat[0] != 6){
      DBG (5, "six5: cmd bad status? %d\n",stat[0]);
      return SANE_STATUS_IO_ERROR;
  }

  DBG (10, "six5: finish\n");

  return ret;
}
