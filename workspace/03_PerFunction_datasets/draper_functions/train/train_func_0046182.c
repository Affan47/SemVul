_cpp_read_logical_line_trad (pfile)
     cpp_reader *pfile;
{
  do
    {
      if (pfile->buffer->cur == pfile->buffer->rlimit)
	{
	  bool stop = true;


	  if (pfile->buffer->prev)
	    {
	      stop = pfile->buffer->return_at_eof;
	      _cpp_pop_buffer (pfile);
	    }

	  if (stop)
	    return false;
	}

      scan_out_logical_line (pfile, NULL);
    }
  while (pfile->state.skipping);

  return true;
}
