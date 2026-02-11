history_truncate_file (fname, lines)
     char *fname;
     register int lines;
{
  register int i;
  int file, chars_read;
  char *buffer = (char *)NULL, *filename;
  struct stat finfo;

  filename = history_filename (fname);
  file = open (filename, O_RDONLY, 0666);

  if (file == -1 || xfstat (file, &finfo) == -1)
    goto truncate_exit;

  buffer = xmalloc ((int)finfo.st_size + 1);
  chars_read = read (file, buffer, finfo.st_size);
  close (file);

  if (chars_read <= 0)
    goto truncate_exit;


  for (i = chars_read - 1; lines && i; i--)
    {
      if (buffer[i] == '\n')
	lines--;
    }


  for ( ; i; i--)
    if (buffer[i] == '\n')
      {
	i++;
	break;
      }


  if (i && ((file = open (filename, O_WRONLY|O_TRUNC, 0666)) != -1))
    {
      write (file, buffer + i, finfo.st_size - i);
      close (file);
    }

 truncate_exit:
  if (buffer)
    xfree (buffer);

  xfree (filename);
  return 0;
}
