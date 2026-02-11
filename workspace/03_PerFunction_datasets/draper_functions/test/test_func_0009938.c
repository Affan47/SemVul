os_close (p, fd)
     host_callback *p;
     int fd;
{
  int result;
  int i, next;

  result = fdbad (p, fd);
  if (result)
    return result;


  for (i = fd; (next = p->fd_buddy[i]) != fd; )
    i = next;
  if (fd != i)
    p->fd_buddy[i] = p->fd_buddy[fd];
  else
    {
      if (p->ispipe[fd])
	{
	  int other = p->ispipe[fd];
	  int reader, writer;

	  if (other > 0)
	    {

	      reader = fd;
	      writer = other;
	    }
	  else
	    {

	      writer = fd;
	      reader = -other;
	    }


	  if (p->pipe_buffer[writer].buffer != NULL)
	    {
	      (*p->pipe_empty) (p, reader, writer);
	      free (p->pipe_buffer[writer].buffer);
	      p->pipe_buffer[writer].buffer = NULL;
	    }


	  p->pipe_buffer[fd].size = 0;
	  p->ispipe[fd] = 0;


	  if (fd != abs (other))
	    p->ispipe[abs (other)] = -other;
	  p->fd_buddy[fd] = -1;
	  return 0;
	}

      result = wrap (p, close (fdmap (p, fd)));
    }
  p->fd_buddy[fd] = -1;

  return result;
}
