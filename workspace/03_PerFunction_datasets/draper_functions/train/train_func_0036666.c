read_data (Ma1509_Scanner * s, SANE_Byte * buffer, SANE_Int * size)
{
  size_t local_size = *size;
  SANE_Status status;

  status = sanei_usb_read_bulk (s->fd, buffer, &local_size);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (1, "read_data: sanei_usb_read_bulk failed: %s\n",
	   sane_strstatus (status));
      return status;
    }
  *size = local_size;
  return status;
}
