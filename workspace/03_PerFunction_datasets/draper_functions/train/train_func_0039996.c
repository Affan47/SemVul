lx_scan_sg (int exclude_devnum, char *name, size_t name_len,
		int host, int channel, int id, int lun)
  {
    int dev_fd, k, missed;

    if (-1 == lx_sg_dev_base)
      return 0;
    for (k = 0, missed = 0; (missed < SCAN_MISSES) && (k < 255);
	 ++k, ++missed)
      {
	DBG (2, "lx_scan_sg: k=%d, exclude=%d, missed=%d\n", k,
	     exclude_devnum, missed);
	if (k == exclude_devnum)
	  {
	    missed = 0;
	    continue;
	  }
	if ((dev_fd = lx_mk_devicename (k, name, name_len)) >= 0)
	  {
	    missed = 0;
	    if (lx_chk_id (dev_fd, host, channel, id, lun))
	      {
		close (dev_fd);
		return 1;
	      }
	    close (dev_fd);
	  }
	else if (-1 == dev_fd)
	  missed = 0;
      }
    return 0;
  }
