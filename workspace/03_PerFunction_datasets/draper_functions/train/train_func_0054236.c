read_ints (int        fd,
	   int       *buf,
	   int        n_ints_in_buf,
	   int       *n_ints_read,
	   DBusError *error)
{
  size_t bytes = 0;
  ReadStatus retval;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  retval = READ_STATUS_OK;

  while (TRUE)
    {
      ssize_t chunk;
      size_t to_read;

      to_read = sizeof (int) * n_ints_in_buf - bytes;

      if (to_read == 0)
        break;

    again:

      chunk = read (fd,
                    ((char*)buf) + bytes,
                    to_read);

      if (chunk < 0 && errno == EINTR)
        goto again;

      if (chunk < 0)
        {
          dbus_set_error (error,
			  DBUS_ERROR_SPAWN_FAILED,
			  "Failed to read from child pipe (%s)",
			  _dbus_strerror (errno));

          retval = READ_STATUS_ERROR;
          break;
        }
      else if (chunk == 0)
        {
          retval = READ_STATUS_EOF;
          break;
        }
      else
	bytes += chunk;
    }

  *n_ints_read = (int)(bytes / sizeof(int));

  return retval;
}
