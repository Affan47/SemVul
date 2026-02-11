umax_wait_scanner(Umax_Device *dev)
{
 SANE_Status status;
 int cnt = 0;

  DBG(DBG_proc, "wait_scanner\n");

  do
  {
    if (cnt > 100)
    {
      DBG(DBG_warning, "scanner does not get ready\n");
      return -1;
    }

    status = umax_scsi_cmd(dev, test_unit_ready.cmd, test_unit_ready.size, NULL, NULL);
    cnt++;

    if (status)
    {
      if (cnt == 1)
      {
        DBG(DBG_info2, "scanner reports %s, waiting ...\n", sane_strstatus(status));
      }

      usleep(500000);
    }
  } while (status != SANE_STATUS_GOOD );

  DBG(DBG_info, "scanner ready\n");

  return status;
}
