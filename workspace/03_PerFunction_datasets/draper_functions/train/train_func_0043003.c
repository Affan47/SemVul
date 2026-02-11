status_open (const char *filename,
	     const int refresh_freq,
	     const int msglevel,
	     const struct virtual_output *vout,
	     const unsigned int flags)
{
  struct status_output *so = NULL;
  if (filename || msglevel >= 0 || vout)
    {
      ALLOC_OBJ_CLEAR (so, struct status_output);
      so->flags = flags;
      so->msglevel = msglevel;
      so->vout = vout;
      so->fd = -1;
      buf_reset (&so->read_buf);
      event_timeout_clear (&so->et);
      if (filename)
	{
	  switch (so->flags)
	    {
#ifdef _MSC_VER
            case STATUS_OUTPUT_WRITE:
              so->fd = open (filename,
                             O_CREAT | O_TRUNC | O_WRONLY,
			     _S_IREAD | _S_IWRITE);
              break;
            case STATUS_OUTPUT_READ:
              so->fd = open (filename,
                             O_RDONLY,
			     _S_IREAD | _S_IWRITE);
              break;
            case STATUS_OUTPUT_READ|STATUS_OUTPUT_WRITE:
              so->fd = open (filename,
                             O_CREAT | O_RDWR,
			     _S_IREAD | _S_IWRITE);
              break;
#else
	    case STATUS_OUTPUT_WRITE:
	      so->fd = open (filename,
			     O_CREAT | O_TRUNC | O_WRONLY,
			     S_IRUSR | S_IWUSR);
	      break;
	    case STATUS_OUTPUT_READ:
	      so->fd = open (filename,
			     O_RDONLY,
			     S_IRUSR | S_IWUSR);
	      break;
	    case STATUS_OUTPUT_READ|STATUS_OUTPUT_WRITE:
	      so->fd = open (filename,
			     O_CREAT | O_RDWR,
			     S_IRUSR | S_IWUSR);
	      break;
#endif
	    default:
	      ASSERT (0);
	    }
	  if (so->fd >= 0)
	    {
	      so->filename = string_alloc (filename, NULL);


	      if (so->flags & STATUS_OUTPUT_READ)
		so->read_buf = alloc_buf (512);
	    }
	  else
	    {
	      msg (M_WARN, "Note: cannot open %s for %s", filename, print_status_mode (so->flags));
	      so->errors = true;
	    }
	}
      else
	so->flags = STATUS_OUTPUT_WRITE;

      if ((so->flags & STATUS_OUTPUT_WRITE) && refresh_freq > 0)
	{
	  event_timeout_init (&so->et, refresh_freq, 0);
	}
    }
  return so;
}
