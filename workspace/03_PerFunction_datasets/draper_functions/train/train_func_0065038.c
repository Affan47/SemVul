attach_scanner (const char *devicename, Sceptre_Scanner ** devp)
{
  Sceptre_Scanner *dev;
  int sfd;

  DBG (DBG_sane_proc, "attach_scanner: %s\n", devicename);

  if (devp)
    *devp = NULL;


  for (dev = first_dev; dev; dev = dev->next)
    {
      if (strcmp (dev->sane.name, devicename) == 0)
	{
	  if (devp)
	    {
	      *devp = dev;
	    }
	  DBG (DBG_info, "device is already known\n");
	  return SANE_STATUS_GOOD;
	}
    }


  dev = sceptre_init ();
  if (dev == NULL)
    {
      DBG (DBG_error, "ERROR: not enough memory\n");
      return SANE_STATUS_NO_MEM;
    }

  DBG (DBG_info, "attach_scanner: opening %s\n", devicename);

  if (sanei_scsi_open (devicename, &sfd, sceptre_sense_handler, dev) != 0)
    {
      DBG (DBG_error, "ERROR: attach_scanner: open failed\n");
      sceptre_free (dev);
      return SANE_STATUS_INVAL;
    }


  dev->devicename = strdup (devicename);
  dev->sfd = sfd;


  if (sceptre_identify_scanner (dev) == SANE_FALSE)
    {
      DBG (DBG_error,
	   "ERROR: attach_scanner: scanner-identification failed\n");
      sceptre_free (dev);
      return SANE_STATUS_INVAL;
    }

  sceptre_close (dev);


  dev->sane.name = dev->devicename;
  dev->sane.vendor = scanners[dev->scnum].real_vendor;
  dev->sane.model = scanners[dev->scnum].real_product;
  dev->sane.type = SANE_I18N ("flatbed scanner");

  dev->resolution_range.min = SANE_FIX (50);
  dev->resolution_range.max = SANE_FIX (1200);
  dev->resolution_range.quant = SANE_FIX (1);


  dev->x_range.min = SANE_FIX (0);
  dev->x_range.max = SANE_FIX (215.90);
  dev->x_range.quant = 0;

  dev->y_range.min = SANE_FIX (0);
  dev->y_range.max = SANE_FIX (297.14);
  dev->y_range.quant = SANE_FIX (0);


  dev->next = first_dev;
  first_dev = dev;

  if (devp)
    {
      *devp = dev;
    }

  num_devices++;

  DBG (DBG_proc, "attach_scanner: exit\n");

  return SANE_STATUS_GOOD;
}
