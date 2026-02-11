gl843_bulk_read_data (Genesys_Device * dev, uint8_t addr,
		      uint8_t * data, size_t len)
{
  SANE_Status status;
  size_t size;
  uint8_t outdata[8];

  DBGSTART;
  DBG (DBG_io,
       "gl843_bulk_read_data: requesting %lu bytes from 0x%02x addr\n",
       (u_long) len, addr);

  status =
    sanei_usb_control_msg (dev->dn, REQUEST_TYPE_OUT, REQUEST_REGISTER,
			   VALUE_SET_REGISTER, 0, 1, &addr);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "write_data: failed to set register address %s\n",
	   sane_strstatus (status));
      return status;
    }

  if (len == 0)
    return SANE_STATUS_GOOD;

  outdata[0] = BULK_IN;
  outdata[1] = BULK_RAM;
  outdata[2] = VALUE_BUFFER;
  outdata[3] = 0;
  outdata[4] = (len & 0xff);
  outdata[5] = ((len >> 8) & 0xff);
  outdata[6] = ((len >> 16) & 0xff);
  outdata[7] = ((len >> 24) & 0xff);

  status =
    sanei_usb_control_msg (dev->dn, REQUEST_TYPE_OUT, REQUEST_BUFFER,
			   VALUE_BUFFER, INDEX, sizeof (outdata), outdata);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl843_bulk_read_data failed while writing command: %s\n",
	   sane_strstatus (status));
      return status;
    }

  while (len)
    {
      if (len > 0xF000)
	size = 0xF000;
      else
	size = len;
      if (size >= 512)
	{
	  size /= 512;
	  size *= 512;
	}

      DBG (DBG_io2,
	   "gl843_bulk_read_data: trying to read %lu bytes of data\n",
	   (u_long) size);

      status = sanei_usb_read_bulk (dev->dn, data, &size);
      if (status != SANE_STATUS_GOOD)
	{
	  DBG (DBG_error,
	       "gl843_bulk_read_data failed while reading bulk data: %s\n",
	       sane_strstatus (status));
	  return status;
	}

      DBG (DBG_io2,
	   "gl843_bulk_read_data read %lu bytes, %lu remaining\n",
	   (u_long) size, (u_long) (len - size));

      len -= size;
      data += size;
    }

  DBGCOMPLETED;
  return SANE_STATUS_GOOD;
}
