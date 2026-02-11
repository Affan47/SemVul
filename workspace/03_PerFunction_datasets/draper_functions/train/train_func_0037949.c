mapfile (fd, line_count_goal, origin, nskip, callback_quantum, callback, array_name, flags)
     int fd;
     long line_count_goal, origin, nskip, callback_quantum;
     char *callback, *array_name;
     int flags;
{
  char *line;
  size_t line_length;
  unsigned int array_index, line_count;
  SHELL_VAR *entry;
  int unbuffered_read;

  line = NULL;
  line_length = 0;
  unbuffered_read = 0;


  entry = find_or_make_array_variable (array_name, 1);
  if (entry == 0 || readonly_p (entry) || noassign_p (entry))
    {
      if (entry && readonly_p (entry))
	err_readonly (array_name);

      return (EXECUTION_FAILURE);
    }
  else if (array_p (entry) == 0)
    {
      builtin_error (_("%s: not an indexed array"), array_name);
      return (EXECUTION_FAILURE);
    }

  if (flags & MAPF_CLEARARRAY)
    array_flush (array_cell (entry));

#ifndef __CYGWIN__
  unbuffered_read = (lseek (fd, 0L, SEEK_CUR) < 0) && (errno == ESPIPE);
#else
  unbuffered_read = 1;
#endif

  zreset ();


  for (line_count = 0; line_count < nskip; line_count++)
    if (zgetline (fd, &line, &line_length, unbuffered_read) < 0)
      break;

  line = 0;
  line_length = 0;


  interrupt_immediately++;
  for (array_index = origin, line_count = 1;
       zgetline (fd, &line, &line_length, unbuffered_read) != -1;
       array_index++, line_count++)
    {

      if (line_count_goal != 0 && line_count > line_count_goal)
	break;


      if (flags & MAPF_CHOP)
	do_chop (line);


      if (callback && line_count && (line_count % callback_quantum) == 0)
	{
	  run_callback (callback, array_index);


	  if (unbuffered_read == 0)
	    zsyncfd (fd);
	}

      bind_array_element (entry, array_index, line, 0);
    }

  xfree (line);

  if (unbuffered_read == 0)
    zsyncfd (fd);

  interrupt_immediately--;
  return EXECUTION_SUCCESS;
}
