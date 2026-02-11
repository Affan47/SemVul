_dbus_file_get_contents (DBusString       *str,
                         const DBusString *filename,
                         DBusError        *error)
{
  int fd;
  struct stat sb;
  int orig_len;
  int total;
  const char *filename_c;

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);

  filename_c = _dbus_string_get_const_data (filename);


  fd = open (filename_c, O_RDONLY | O_BINARY);
  if (fd < 0)
    {
      dbus_set_error (error, _dbus_error_from_errno (errno),
                      "Failed to open \"%s\": %s",
                      filename_c,
                      _dbus_strerror (errno));
      return FALSE;
    }

  _dbus_verbose ("file fd %d opened\n", fd);

  if (fstat (fd, &sb) < 0)
    {
      dbus_set_error (error, _dbus_error_from_errno (errno),
                      "Failed to stat \"%s\": %s",
                      filename_c,
                      _dbus_strerror (errno));

      _dbus_verbose ("fstat() failed: %s",
                     _dbus_strerror (errno));

      _dbus_close (fd, NULL);

      return FALSE;
    }

  if (sb.st_size > _DBUS_ONE_MEGABYTE)
    {
      dbus_set_error (error, DBUS_ERROR_FAILED,
                      "File size %lu of \"%s\" is too large.",
                      (unsigned long) sb.st_size, filename_c);
      _dbus_close (fd, NULL);
      return FALSE;
    }

  total = 0;
  orig_len = _dbus_string_get_length (str);
  if (sb.st_size > 0 && S_ISREG (sb.st_mode))
    {
      int bytes_read;

      while (total < (int) sb.st_size)
        {
          bytes_read = _dbus_read (fd, str,
                                   sb.st_size - total);
          if (bytes_read <= 0)
            {
              dbus_set_error (error, _dbus_error_from_errno (errno),
                              "Error reading \"%s\": %s",
                              filename_c,
                              _dbus_strerror (errno));

              _dbus_verbose ("read() failed: %s",
                             _dbus_strerror (errno));

              _dbus_close (fd, NULL);
              _dbus_string_set_length (str, orig_len);
              return FALSE;
            }
          else
            total += bytes_read;
        }

      _dbus_close (fd, NULL);
      return TRUE;
    }
  else if (sb.st_size != 0)
    {
      _dbus_verbose ("Can only open regular files at the moment.\n");
      dbus_set_error (error, DBUS_ERROR_FAILED,
                      "\"%s\" is not a regular file",
                      filename_c);
      _dbus_close (fd, NULL);
      return FALSE;
    }
  else
    {
      _dbus_close (fd, NULL);
      return TRUE;
    }
}
