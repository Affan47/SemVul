os_write (p, fd, buf, len)
     host_callback *p;
     int fd;
     const char *buf;
     int len;
{
  int result;
  int real_fd;

  result = fdbad (p, fd);
  if (result)
    return result;

  if (p->ispipe[fd])
    {
      int reader = -p->ispipe[fd];


      if (reader < 0)
	{
	  p->last_errno = EBADF;
	  return -1;
	}


      if (reader == fd)
	{
	  p->last_errno = EPIPE;
	  return -1;
	}


      if (p->pipe_buffer[fd].size + len > 10 * PIPE_BUF)
	{
	  p->last_errno = EFBIG;
	  return -1;
	}

      p->pipe_buffer[fd].buffer
	= xrealloc (p->pipe_buffer[fd].buffer, p->pipe_buffer[fd].size + len);
      memcpy (p->pipe_buffer[fd].buffer + p->pipe_buffer[fd].size,
	      buf, len);
      p->pipe_buffer[fd].size += len;

      (*p->pipe_nonempty) (p, reader, fd);
      return len;
    }

  real_fd = fdmap (p, fd);
  switch (real_fd)
    {
    default:
      result = wrap (p, write (real_fd, buf, len));
      break;
    case 1:
      result = p->write_stdout (p, buf, len);
      break;
    case 2:
      result = p->write_stderr (p, buf, len);
      break;
    }
  return result;
}
