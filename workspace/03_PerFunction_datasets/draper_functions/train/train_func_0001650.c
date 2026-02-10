sceptre_get_status (Sceptre_Scanner * dev, size_t * data_left)
{
  size_t size;
  CDB cdb;
  SANE_Status status;

  DBG (DBG_proc, "sceptre_get_status: enter\n");


  size = 0x10;
  MKSCSI_GET_DATA_BUFFER_STATUS (cdb, 1, size);
  status = sanei_scsi_cmd2 (dev->sfd, cdb.data, cdb.len,
			    NULL, 0, dev->buffer, &size);

  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error, "sceptre_get_status: cannot get buffer status\n");
      *data_left = 0;
      return (SANE_STATUS_IO_ERROR);
    }

  if (size != 16)
    {
      DBG (DBG_error,
	   "sceptre_get_status: invalid data size returned (%ld)\n",
	   (long) size);
      return (SANE_STATUS_IO_ERROR);
    }

  hexdump (DBG_info2, "GET BUFFER STATUS result", dev->buffer, 16);


  *data_left = B32TOI (&dev->buffer[8]);

  if (dev->raster_real == 0)
    {

      dev->raster_real = B16TOI (&dev->buffer[12]) * 3;
      dev->params.lines = B16TOI (&dev->buffer[12]);
      dev->params.pixels_per_line = B16TOI (&dev->buffer[14]);
    }

  DBG (DBG_proc, "sceptre_get_status: exit, data_left=%ld\n",
       (long) *data_left);

  return (SANE_STATUS_GOOD);
}
