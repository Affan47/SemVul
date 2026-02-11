wait_scanner (Coolscan_t * s)
{
  int ret = -1;
  int cnt = 0;
  DBG (10, "wait_scanner: Testing if scanner is ready\n");

  while (ret != 0)
    {
      ret = do_scsi_cmd (s->sfd, test_unit_ready.cmd,
			 test_unit_ready.size, 0, 0);

      if (ret == SANE_STATUS_DEVICE_BUSY)
	{
	  usleep (500000);
	  if (cnt++ > 40)
	    {
	      DBG (1, "wait_scanner: scanner does NOT get ready\n");
	      return -1;
	    }
	}
      else if (ret == SANE_STATUS_GOOD)
	{
	  DBG (10, "wait_scanner: scanner is ready\n");
	  return ret;
	}
      else
	{
	  DBG (1, "wait_scanner: test unit ready failed (%s)\n",
	       sane_strstatus (ret));
	}
    }
  return 0;
}
