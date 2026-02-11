helper_read_line(FILE *fh)
{
  char *buffer = safe_malloc(LINE_BUFFER_STEP);
  int buffer_size = LINE_BUFFER_STEP;
  int buffer_pos = 0;
  int i, done = 0;

  do
    {
      if (!fgets(buffer + buffer_pos, buffer_size - buffer_pos, fh))
	{
	  free(buffer);
	  return NULL;
	}


      for (i = buffer_pos; i < buffer_size; i++)
	if (buffer[i] == '\n')
	  {
	    buffer[i] = '\0';
	    done = 1;
	    break;
	  }

      if (!done)
	{

	  buffer = safe_realloc(buffer, buffer_size + LINE_BUFFER_STEP);
	  buffer_pos = buffer_size - 1;
	  buffer_size += LINE_BUFFER_STEP;
	}
    }
  while (!done);

  return buffer;
}
