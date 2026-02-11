sanei_usb_get_descriptor( SANE_Int dn, struct sanei_usb_dev_descriptor *desc )
{
  if (dn >= device_number || dn < 0)
    {
      DBG (1,
	   "sanei_usb_get_descriptor: dn >= device number || dn < 0, dn=%d\n",
	   dn);
      return SANE_STATUS_INVAL;
    }

  DBG (5, "sanei_usb_get_descriptor\n");
#ifdef HAVE_LIBUSB
    {
	  struct usb_device_descriptor *usb_descr;

	  usb_descr = &(devices[dn].libusb_device->descriptor);
	  desc->desc_type = usb_descr->bDescriptorType;
	  desc->bcd_usb   = usb_descr->bcdUSB;
	  desc->bcd_dev   = usb_descr->bcdDevice;
	  desc->dev_class = usb_descr->bDeviceClass;

	  desc->dev_sub_class   = usb_descr->bDeviceSubClass;
	  desc->dev_protocol    = usb_descr->bDeviceProtocol;
	  desc->max_packet_size = usb_descr->bMaxPacketSize0;
	  return SANE_STATUS_GOOD;
    }
#elif defined(HAVE_LIBUSB_1_0)
    {
      struct libusb_device_descriptor lu_desc;
      int ret;

      ret = libusb_get_device_descriptor (devices[dn].lu_device, &lu_desc);
      if (ret < 0)
	{
	  DBG (1,
	       "sanei_usb_get_descriptor: libusb error: %s\n",
	       sanei_libusb_strerror (ret));

	  return SANE_STATUS_INVAL;
	}

      desc->desc_type = lu_desc.bDescriptorType;
      desc->bcd_usb   = lu_desc.bcdUSB;
      desc->bcd_dev   = lu_desc.bcdDevice;
      desc->dev_class = lu_desc.bDeviceClass;

      desc->dev_sub_class   = lu_desc.bDeviceSubClass;
      desc->dev_protocol    = lu_desc.bDeviceProtocol;
      desc->max_packet_size = lu_desc.bMaxPacketSize0;
      return SANE_STATUS_GOOD;
    }
#else
    {
      DBG (1, "sanei_usb_get_descriptor: libusb support missing\n");
      return SANE_STATUS_UNSUPPORTED;
    }
#endif
}
