wait_ready(int fd)
{
  SANE_Status status;
  int retry = 0;

  while ((status = test_unit_ready (fd)) != SANE_STATUS_GOOD)
  {
    DBG (5, "wait_ready failed (%d)\n", retry);
    if (retry++ > 15){
	return SANE_STATUS_IO_ERROR;
    }
    sleep(3);
  }
  return (status);

}
