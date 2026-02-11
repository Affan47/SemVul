parse_opt_set_default_format_from_file (const char *file)
{
  static struct obstack stk;
  FILE *fp;
  char *buf = NULL;
  size_t size = 0;

  fp = fopen (file, "r");
  if (!fp)
    error (EXIT_FAILURE, errno, "cannot open format file %s", file);

  obstack_init (&stk);
  while (getline (&buf, &size, fp) > 0)
    {
      size_t len = strlen (buf);

      if (len >= 1 && buf[len-1] == '\n')
	len--;

      if (len == 0 || is_comment_line (buf, len))
	continue;
      obstack_grow (&stk, buf, len);
    }
  free (buf);
  fclose (fp);
  obstack_1grow (&stk, 0);
  default_format = obstack_finish (&stk);
}
