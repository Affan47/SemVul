attachLexmark (SANE_String_Const devname)
{
  Lexmark_Device *lexmark_device;
  SANE_Int dn, vendor, product, variant;
  SANE_Status status;

  DBG (2, "attachLexmark: devname=%s\n", devname);

  for (lexmark_device = first_lexmark_device; lexmark_device;
       lexmark_device = lexmark_device->next)
    {

      if (strcmp (lexmark_device->sane.name, devname) == 0)
      {
        lexmark_device->missing = SANE_FALSE;
	return SANE_STATUS_GOOD;
      }
    }

  lexmark_device = (Lexmark_Device *) malloc (sizeof (Lexmark_Device));
  if (lexmark_device == NULL)
    return SANE_STATUS_NO_MEM;

#ifdef FAKE_USB
  status = SANE_STATUS_GOOD;
#else
  status = sanei_usb_open (devname, &dn);
#endif
  if (status != SANE_STATUS_GOOD)
    {
      DBG (1, "attachLexmark: couldn't open device `%s': %s\n", devname,
	   sane_strstatus (status));
      return status;
    }
  else
    DBG (2, "attachLexmark: device `%s' successfully opened\n", devname);

#ifdef FAKE_USB
  status = SANE_STATUS_GOOD;

  vendor = 0x043d;
  product = 0x007c;
  variant = 0xb2;
#else
  variant = 0;
  status = sanei_usb_get_vendor_product (dn, &vendor, &product);
#endif
  if (status != SANE_STATUS_GOOD)
    {
      DBG (1,
	   "attachLexmark: couldn't get vendor and product ids of device `%s': %s\n",
	   devname, sane_strstatus (status));
#ifndef FAKE_USB
      sanei_usb_close (dn);
#endif
      return status;
    }
#ifndef FAKE_USB
  sanei_usb_close (dn);
#endif

  DBG (2, "attachLexmark: testing device `%s': 0x%04x:0x%04x, variant=%d\n",
       devname, vendor, product, variant);
  if (sanei_lexmark_low_assign_model (lexmark_device,
				      devname,
				      vendor,
				      product, variant) != SANE_STATUS_GOOD)
    {
      DBG (2, "attachLexmark: unsupported device `%s': 0x%04x:0x%04x\n",
	   devname, vendor, product);
      return SANE_STATUS_UNSUPPORTED;
    }


  status = sanei_lexmark_low_open_device (lexmark_device);
  sanei_usb_close (lexmark_device->devnum);


  sanei_lexmark_low_init (lexmark_device);


  lexmark_device->x_dpi = 75;
  lexmark_device->y_dpi = 75;


  lexmark_device->read_buffer = NULL;


  lexmark_device->threshold = 0x80;

  lexmark_device->shading_coeff = NULL;


  lexmark_device->missing = SANE_FALSE;


  lexmark_device->next = first_lexmark_device;
  first_lexmark_device = lexmark_device;

  num_lexmark_device++;

  return status;
}
