ma1509_cmd (Ma1509_Scanner * s, const SANE_Byte * cmd, SANE_Byte * data,
	    size_t * data_size)
{
  SANE_Status status;
  size_t size;
#define MA1509_WRITE_LIMIT (1024 * 64)
#define MA1509_READ_LIMIT (1024 * 256)

  DBG (5, "ma1509_cmd: fd=%d, cmd=%p, data=%p, data_size=%ld\n",
       s->fd, cmd, data, (long int) (data_size ? *data_size : 0));
  DBG (5, "ma1509_cmd: cmd = %02x %02x %02x %02x %02x %02x %02x %02x \n",
       cmd[0], cmd[1], cmd[2], cmd[3], cmd[4], cmd[5], cmd[6], cmd[7]);


  size = MA1509_COMMAND_LENGTH;
  status = sanei_usb_write_bulk (s->fd, cmd, &size);
  if (status != SANE_STATUS_GOOD || size != MA1509_COMMAND_LENGTH)
    {
      DBG (5,
	   "ma1509_cmd: sanei_usb_write_bulk returned %s (size = %ld, expected %d)\n",
	   sane_strstatus (status), (long int) size, MA1509_COMMAND_LENGTH);
      return status;
    }

  if (cmd[1] == 1)
    {

      if (data && data_size && *data_size)
	{
	  size_t bytes_left = *data_size;
	  DBG (5, "ma1509_cmd: trying to receive %ld bytes of data\n",
	       (long int) *data_size);

	  while (status == SANE_STATUS_GOOD && bytes_left > 0)
	    {
	      size = bytes_left;
	      if (size > MA1509_READ_LIMIT)
		size = MA1509_READ_LIMIT;

	      status =
		sanei_usb_read_bulk (s->fd, data + *data_size - bytes_left,
				     &size);

	      if (status != SANE_STATUS_GOOD)
		{
		  DBG (1, "ma1509_cmd: sanei_usb_read_bulk returned %s\n",
		       sane_strstatus (status));
		  return status;
		}
	      bytes_left -= size;
	      DBG (5, "ma1509_cmd: read %ld bytes, %ld bytes to go\n",
		   (long int) size, (long int) bytes_left);
	    }
	  if (debug_level >= 5)
	    print_data_buffer (data, *data_size);
	}
    }
  else
    {

      if (data && data_size && *data_size)
	{
	  size_t bytes_left = *data_size;

	  DBG (5, "ma1509_cmd: sending %ld bytes of data\n",
	       (long int) *data_size);
	  if (debug_level >= 5)
	    print_data_buffer (data, *data_size);

	  while (status == SANE_STATUS_GOOD && bytes_left > 0)
	    {
	      size = bytes_left;
	      if (size > MA1509_WRITE_LIMIT)
		size = MA1509_WRITE_LIMIT;
	      status =
		sanei_usb_write_bulk (s->fd, data + *data_size - bytes_left,
				      &size);
	      if (status != SANE_STATUS_GOOD)
		{
		  DBG (1, "ma1509_cmd: sanei_usb_write_bulk returned %s\n",
		       sane_strstatus (status));
		  return status;
		}
	      bytes_left -= size;
	      DBG (5, "ma1509_cmd: wrote %ld bytes, %ld bytes to go\n",
		   (long int) size, (long int) bytes_left);
	    }

	}
    }

  DBG (5, "ma1509_cmd: finished: data_size=%ld, status=%s\n",
       (long int) (data_size ? *data_size : 0), sane_strstatus (status));
  return status;
}
