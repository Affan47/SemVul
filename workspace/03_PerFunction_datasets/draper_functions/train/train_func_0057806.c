console_capture (void *data)
{
  uint8_t id = (uint8_t)(intptr_t)data;
  char *line = NULL;
  size_t size;
  FILE *in = fdopen (fd[id].fd[0], "r");

  setlinebuf (in);
  while (getline (&line, &size, in) != -1)
  {
    console_lock ();
    if (!prev_line || strcmp (line, prev_line))
    {
      fputs (line, fd[id].file);
      console_push (line, id);
      set_prev_line (line);
    }
    else
      set_prev_line (NULL);
    console_unlock ();
  }

  free (line);
  return NULL;
}
