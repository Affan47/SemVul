read_more_data (S9036_Scanner * s)
{

  static Byte cmd[] =
  {
    0x28, 0x00,
    0x00,
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00,
    0x00,
  };

  SANE_Status status;
  size_t size;
  int lines_read;
  int bpl = s->params.bytes_per_line;
  unsigned int i;

  if (s->lines_in_scanner == 0)
    {

      status = request_more_data (s);

      if (status != SANE_STATUS_GOOD)
	return status;

    }


  while (1)
    {


      lines_read = s->bufsize / bpl;


      if (!lines_read)
	return SANE_STATUS_INVAL;


      if (lines_read > s->lines_in_scanner)
	lines_read = s->lines_in_scanner;

      set_size (&cmd[6], 3, lines_read);
      size = lines_read * s->params.bytes_per_line;

      DBG (1, "Requesting %d lines, in scanner: %d, total: %d\n", lines_read,
	   s->lines_in_scanner, s->params.lines);

      status = sanei_scsi_cmd (s->fd, cmd, sizeof (cmd), s->buffer, &size);

      if (status != SANE_STATUS_GOOD)
	{
	  if (s->bufsize > 4096)
	    {
	      DBG (1, "sanei_scsi_cmd(): using 4k buffer\n");
	      s->bufsize = 4096;
	      continue;
	    }

	  DBG (1, "sanei_scsi_cmd() = %d\n", status);
	  return SANE_STATUS_IO_ERROR;
	}

      if (size != (unsigned int) lines_read * s->params.bytes_per_line)
	{
	  DBG (1, "sanei_scsi_cmd(): got %lu bytes, expected %d\n",
	       (u_long) size, lines_read * s->params.bytes_per_line);
	  return SANE_STATUS_INVAL;
	}

      DBG (1, "Got %lu bytes\n", (u_long) size);
      break;
    }


  if (s->params.depth != 1)
    for (i = 0; i < size; i++)
      s->buffer[i] = (255 - s->buffer[i]);

  s->in_buffer += size;
  s->lines_in_scanner -= lines_read;
  s->lines_read += lines_read;

  return SANE_STATUS_GOOD;
}
