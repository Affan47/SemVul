history_filename (filename)
     char *filename;
{
  char *return_val = filename ? savestring (filename) : (char *)NULL;

  if (!return_val)
    {
      char *home;
      int home_len;

      home = getenv ("HOME");

      if (!home)
	home = ".";

      home_len = strlen (home);

      return_val = xmalloc (2 + home_len + 8);

      strcpy (return_val, home);
      return_val[home_len] = '/';
      strcpy (return_val + home_len + 1, ".history");
    }

  return (return_val);
}
