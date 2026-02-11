print_filenames (struct file_link **flinkv, enum separator_style separator_style)
{
  struct file_link const *arg;
  struct file_link const *dlink;
  int brace_is_open = 0;
  char *file_name = alloca (sizeof(char) * PATH_MAX);

  while (*flinkv)
    {
      arg = *flinkv++;
      if (*flinkv && (separator_style == ss_braces)
	  && common_prefix_suffix (arg, *flinkv))
	{
	  if (brace_is_open)
	    printf (",%s", root_name (arg->fl_name));
	  else
	    {
	      dlink = arg->fl_parent;
	      if (dlink && dlink != cw_dlink)
		{
		  maybe_relative_file_name (file_name, dlink, cw_dlink);
		  fputs (file_name, stdout);
		  putchar ('/');
		}
	      printf ("{%s", root_name (arg->fl_name));
	    }
	  brace_is_open = 1;
	}
      else
	{
	  if (brace_is_open)
	    printf (",%s}%s", root_name (arg->fl_name), suff_name (arg->fl_name));
	  else
	    {
	      maybe_relative_file_name (file_name, arg, cw_dlink);
	      fputs (file_name, stdout);
	    }
	  brace_is_open = 0;
	  if (*flinkv)
	    {
	      if (separator_style == ss_newline)
		putchar ('\n');
	      else
		putchar (' ');
	    }
	}
    }
  putchar ('\n');
}
