sparse_write (int fildes, char *buf, unsigned int nbyte)
{
  int complete_block_count;
  int leftover_bytes_count;
  int seek_count;
  int write_count;
  char *cur_write_start;
  int lseek_rc;
  int write_rc;
  int i;
  enum { begin, in_zeros, not_in_zeros } state;

  complete_block_count = nbyte / DISKBLOCKSIZE;
  leftover_bytes_count = nbyte % DISKBLOCKSIZE;

  if (delayed_seek_count != 0)
    state = in_zeros;
  else
    state = begin;

  seek_count = delayed_seek_count;

  for (i = 0; i < complete_block_count; ++i)
    {
      switch (state)
	{
	  case begin :
	    if (buf_all_zeros (buf, DISKBLOCKSIZE))
	      {
		seek_count = DISKBLOCKSIZE;
		state = in_zeros;
	      }
	    else
	      {
		cur_write_start = buf;
		write_count = DISKBLOCKSIZE;
		state = not_in_zeros;
	      }
	    buf += DISKBLOCKSIZE;
	    break;

	  case in_zeros :
	    if (buf_all_zeros (buf, DISKBLOCKSIZE))
	      {
		seek_count += DISKBLOCKSIZE;
	      }
	    else
	      {
		lseek (fildes, seek_count, SEEK_CUR);
		cur_write_start = buf;
		write_count = DISKBLOCKSIZE;
		state = not_in_zeros;
	      }
	    buf += DISKBLOCKSIZE;
	    break;

	  case not_in_zeros :
	    if (buf_all_zeros (buf, DISKBLOCKSIZE))
	      {
		write_rc = write (fildes, cur_write_start, write_count);
		seek_count = DISKBLOCKSIZE;
		state = in_zeros;
	      }
	    else
	      {
		write_count += DISKBLOCKSIZE;
	      }
	    buf += DISKBLOCKSIZE;
	    break;
	}
    }

  switch (state)
    {
      case begin :
      case in_zeros :
	delayed_seek_count = seek_count;
	break;

      case not_in_zeros :
	write_rc = write (fildes, cur_write_start, write_count);
	delayed_seek_count = 0;
	break;
    }

  if (leftover_bytes_count != 0)
    {
      if (delayed_seek_count != 0)
	{
	  lseek_rc = lseek (fildes, delayed_seek_count, SEEK_CUR);
	  delayed_seek_count = 0;
	}
      write_rc = write (fildes, buf, leftover_bytes_count);
    }
  return nbyte;
}
