backendDrainOutput(int print_fd,
                   int device_fd)
{
  int		nfds;
  fd_set	input;
  ssize_t	print_bytes,
		bytes;
  char		print_buffer[8192],
		*print_ptr;
  struct timeval timeout;


  fprintf(stderr, "DEBUG: backendDrainOutput(print_fd=%d, device_fd=%d)\n",
          print_fd, device_fd);


  nfds = (print_fd > device_fd ? print_fd : device_fd) + 1;


  for (;;)
  {


    FD_ZERO(&input);
    FD_SET(print_fd, &input);

    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;

    if (select(nfds, &input, NULL, NULL, &timeout) < 0)
      return (-1);

    if (!FD_ISSET(print_fd, &input))
      return (0);

    if ((print_bytes = read(print_fd, print_buffer,
			    sizeof(print_buffer))) < 0)
    {


      if (errno != EAGAIN || errno != EINTR)
      {
	fprintf(stderr, "DEBUG: Read failed: %s\n", strerror(errno));
	_cupsLangPrintFilter(stderr, "ERROR", _("Unable to read print data."));
	return (-1);
      }

      print_bytes = 0;
    }
    else if (print_bytes == 0)
    {


      return (0);
    }

    fprintf(stderr, "DEBUG: Read %d bytes of print data...\n",
	    (int)print_bytes);

    for (print_ptr = print_buffer; print_bytes > 0;)
    {
      if ((bytes = write(device_fd, print_ptr, print_bytes)) < 0)
      {


        if (errno != ENOSPC && errno != ENXIO && errno != EAGAIN &&
	    errno != EINTR && errno != ENOTTY)
	{
	  _cupsLangPrintError("ERROR", _("Unable to write print data"));
	  return (-1);
	}
      }
      else
      {
        fprintf(stderr, "DEBUG: Wrote %d bytes of print data...\n", (int)bytes);

        print_bytes -= bytes;
	print_ptr   += bytes;
      }
    }
  }
}
