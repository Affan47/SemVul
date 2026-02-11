process_include (desc, lineno)
     rtx desc;
     int lineno;
{
  const char *filename = XSTR (desc, 0);
  const char *old_filename;
  int old_lineno;
  char *pathname;
  FILE *input_file;


  if (! IS_ABSOLUTE_PATHNAME (filename))
    {
      struct file_name_list *stackp;


      for (stackp = first_dir_md_include; stackp; stackp = stackp->next)
	{
	  static const char sep[2] = { DIR_SEPARATOR, '\0' };

	  pathname = concat (stackp->fname, sep, filename, NULL);
	  input_file = fopen (pathname, "r");
	  if (input_file != NULL)
	    goto success;
	  free (pathname);
	}
    }

  if (base_dir)
    pathname = concat (base_dir, filename, NULL);
  else
    pathname = xstrdup (filename);
  input_file = fopen (pathname, "r");
  if (input_file == NULL)
    {
      free (pathname);
      message_with_line (lineno, "include file `%s' not found", filename);
      errors = 1;
      return;
    }
 success:


  old_filename = read_rtx_filename;
  old_lineno = read_rtx_lineno;
  read_rtx_filename = pathname;
  read_rtx_lineno = 1;


  while (1)
    {
      rtx desc;
      int c;

      c = read_skip_spaces (input_file);
      if (c == EOF)
	break;

      ungetc (c, input_file);
      lineno = read_rtx_lineno;
      desc = read_rtx (input_file);
      process_rtx (desc, lineno);
    }


  read_rtx_filename = old_filename;
  read_rtx_lineno = old_lineno;

  fclose (input_file);
}
