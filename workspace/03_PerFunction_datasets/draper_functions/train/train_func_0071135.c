wait_ack (struct device_s *dev, int *s)
{
  SANE_Status ret;
  size_t size;
  DBG(100, "Waiting scanner answer on device %s\n",dev->devname);
  do
    {
      size = 32;
      ret =
	sanei_usb_read_bulk (dev->dn, (unsigned char *) dev->packet_data,
			     &size);
    }
  while (SANE_STATUS_EOF == ret || size == 0);
  if (s)
    *s = ntohl (dev->packet_data[4]);
  return ntohl (dev->packet_data[5]);
}
