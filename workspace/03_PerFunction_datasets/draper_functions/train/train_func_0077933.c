read_file (const gchar *scratch_file)
{
  gint          input_fd;
  gint          i;

  input_fd = open (scratch_file, O_RDONLY);
  if (input_fd < 0)
    {
      g_printerr ("Failed to read back scratch file: %s\n", g_strerror (errno));
      return;
    }

  for (i = 0; i < FILE_SIZE; i += BUFFER_SIZE)
    {
      gchar buffer [BUFFER_SIZE];
      gsize bytes_read;

      bytes_read = read (input_fd, buffer, BUFFER_SIZE);
      if (bytes_read < BUFFER_SIZE)
        {
          if (errno == EINTR)
            {
              i -= BUFFER_SIZE - bytes_read;
              continue;
            }

          g_printerr ("Failed to read back scratch file: %s\n", g_strerror (errno));
          close (input_fd);
          return;
        }
    }

  close (input_fd);
}
