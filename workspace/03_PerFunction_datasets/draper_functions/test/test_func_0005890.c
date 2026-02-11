get_max_buffer_size (const char *file)
{
  int fd = -1;
  int buffersize = SCSIBUFFERSIZE, i;
  size_t len;
  char *cc, *cc1, buf[32];

#ifdef HAVE_RESMGR
  fd = rsm_open_device(file, O_RDWR);
#endif

  if (fd == -1)
    fd = open (file, O_RDWR);

  if (fd > 0)
    {
      cc = getenv ("SANE_SG_BUFFERSIZE");
      if (cc)
	{
	  i = strtol (cc, &cc1, 10);
	  if (cc != cc1 && i >= 32768)
	    buffersize = i;
	}

      ioctl (fd, SG_SET_RESERVED_SIZE, &buffersize);
      if (0 == ioctl (fd, SG_GET_RESERVED_SIZE, &buffersize))
	{
	  if (buffersize < sanei_scsi_max_request_size)
	    sanei_scsi_max_request_size = buffersize;
	  close (fd);
	  DBG (4, "get_max_buffer_size for %s: %i\n", file,
	       sanei_scsi_max_request_size);
	  return SANE_STATUS_GOOD;
	}
      else
	{
	  close (fd);

	  fd = open ("/proc/sys/kernel/sg-big-buff", O_RDONLY);
	  if (fd > 0 && (len = read (fd, buf, sizeof (buf) - 1)) > 0)
	    {
	      buf[len] = '\0';
	      sanei_scsi_max_request_size = atoi (buf);
	      close (fd);
	    }
	  else
	    sanei_scsi_max_request_size = buffersize < SG_BIG_BUFF ?
	      buffersize : SG_BIG_BUFF;
	  return SANE_STATUS_IO_ERROR;
	}
    }
  else
    return SANE_STATUS_GOOD;
}
