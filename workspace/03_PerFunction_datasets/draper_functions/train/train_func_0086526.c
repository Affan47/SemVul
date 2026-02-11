accurate_line_read(Genesys_Device * dev,
                                      SANE_Byte *buffer,
                                      size_t size)
{
  SANE_Status status;
  status = dev->model->cmd_set->bulk_read_data (dev, 0x45, buffer, size);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "accurate_line_read: failed to read %lu bytes (%s)\n",
	   (u_long) size, sane_strstatus (status));
      return SANE_STATUS_IO_ERROR;
    }


  dev->oe_buffer.avail = size;
  dev->oe_buffer.pos = 0;
  return status;
}
