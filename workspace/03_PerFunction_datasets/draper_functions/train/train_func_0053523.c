attach (SANE_String_Const devname, Genesys_Device ** devp, SANE_Bool may_wait)
{
  Genesys_Device *dev = 0;
  SANE_Int dn, vendor, product;
  SANE_Status status;
  unsigned int i;


  DBG (DBG_proc, "attach: start: devp %s NULL, may_wait = %d\n",
       devp ? "!=" : "==", may_wait);

  if (devp)
    *devp = 0;

  if (!devname)
    {
      DBG (DBG_error, "attach: devname == NULL\n");
      return SANE_STATUS_INVAL;
    }

  for (dev = first_dev; dev; dev = dev->next)
    {
      if (strcmp (dev->file_name, devname) == 0)
	{
	  if (devp)
	    *devp = dev;
	  DBG (DBG_info, "attach: device `%s' was already in device list\n",
	       devname);
	  return SANE_STATUS_GOOD;
	}
    }

  DBG (DBG_info, "attach: trying to open device `%s'\n", devname);

  status = sanei_usb_open (devname, &dn);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_warn, "attach: couldn't open device `%s': %s\n", devname,
	   sane_strstatus (status));
      return status;
    }
  else
    DBG (DBG_info, "attach: device `%s' successfully opened\n", devname);

  status = sanei_usb_get_vendor_product (dn, &vendor, &product);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "attach: couldn't get vendor and product ids of device `%s': %s\n",
	   devname, sane_strstatus (status));
      return status;
    }


  if(vendor == 0x04da && product == 0x100f)
    {
      present=SANE_FALSE;
      sanei_usb_find_devices (vendor, 0x1006, check_present);
      sanei_usb_find_devices (vendor, 0x1007, check_present);
      sanei_usb_find_devices (vendor, 0x1010, check_present);
      if(present==SANE_FALSE)
        {
          DBG (DBG_error,"attach: master device not present\n");
          return SANE_STATUS_INVAL;
        }
    }

  for (i = 0; i < MAX_SCANNERS && genesys_usb_device_list[i].model != 0; i++)
    {
      if (vendor == genesys_usb_device_list[i].vendor &&
	  product == genesys_usb_device_list[i].product)
	{
	  dev = malloc (sizeof (*dev));
	  if (!dev)
	    return SANE_STATUS_NO_MEM;
	  break;
	}
    }

  if (!dev)
    {
      DBG (DBG_error,
	   "attach: vendor %d product %d is not supported by this backend\n",
	   vendor, product);
      return SANE_STATUS_INVAL;
    }

  dev->file_name = strdup (devname);
  if (!dev->file_name)
    {
      free(dev);
      return SANE_STATUS_NO_MEM;
    }

  dev->model = genesys_usb_device_list[i].model;
  dev->vendorId = genesys_usb_device_list[i].vendor;
  dev->productId = genesys_usb_device_list[i].product;
  dev->already_initialized = SANE_FALSE;

  DBG (DBG_info, "attach: found %s flatbed scanner %s at %s\n",
       dev->model->vendor, dev->model->model, dev->file_name);
  add_device(dev);

  if (devp)
    *devp = dev;
  sanei_usb_close (dn);
  DBGCOMPLETED;
  return SANE_STATUS_GOOD;
}
