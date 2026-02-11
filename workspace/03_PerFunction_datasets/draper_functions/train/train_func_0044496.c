scan_diff_line (scan_ptr, set_start, set_length, limit, leadingchar)
     char *scan_ptr, **set_start;
     size_t *set_length;
     char *limit;
     int leadingchar;
{
  char *line_ptr;

  if (!(scan_ptr[0] == leadingchar
	&& scan_ptr[1] == ' '))
    diff3_fatal ("invalid diff format; incorrect leading line chars");

  *set_start = line_ptr = scan_ptr + 2;
  while (*line_ptr++ != '\n')
    ;


  *set_length = line_ptr - *set_start;
  if (line_ptr < limit && *line_ptr == '\\')
    {
      if (! edscript)
	{
	  --*set_length;
	  line_ptr++;
	  while (*line_ptr++ != '\n')
	    ;
	}
      else
	{
	  char *serr;

	  line_ptr++;
	  serr = line_ptr;
	  while (*line_ptr++ != '\n')
	    ;
	  line_ptr[-1] = '\0';
	  diff_error ("%s", serr, 0);
	  line_ptr[-1] = '\n';
	}
    }

  return line_ptr;
}
