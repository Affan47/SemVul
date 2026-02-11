_cpp_process_line_notes (cpp_reader *pfile, int in_comment)
{
  cpp_buffer *buffer = pfile->buffer;

  for (;;)
    {
      _cpp_line_note *note = &buffer->notes[buffer->cur_note];
      unsigned int col;

      if (note->pos > buffer->cur)
	break;

      buffer->cur_note++;
      col = CPP_BUF_COLUMN (buffer, note->pos + 1);

      if (note->type == '\\' || note->type == ' ')
	{
	  if (note->type == ' ' && !in_comment)
	    cpp_error_with_line (pfile, CPP_DL_WARNING, pfile->line, col,
				 "backslash and newline separated by space");

	  if (buffer->next_line > buffer->rlimit)
	    {
	      cpp_error_with_line (pfile, CPP_DL_PEDWARN, pfile->line, col,
				   "backslash-newline at end of file");

	      buffer->next_line = buffer->rlimit;
	    }

	  buffer->line_base = note->pos;
	  pfile->line++;
	}
      else if (_cpp_trigraph_map[note->type])
	{
	  if (CPP_OPTION (pfile, warn_trigraphs)
	      && (!in_comment || warn_in_comment (pfile, note)))
	    {
	      if (CPP_OPTION (pfile, trigraphs))
		cpp_error_with_line (pfile, CPP_DL_WARNING, pfile->line, col,
				     "trigraph ??%c converted to %c",
				     note->type,
				     (int) _cpp_trigraph_map[note->type]);
	      else
		{
		  cpp_error_with_line
		    (pfile, CPP_DL_WARNING, pfile->line, col,
		     "trigraph ??%c ignored, use -trigraphs to enable",
		     note->type);
		}
	    }
	}
      else
	abort ();
    }
}
