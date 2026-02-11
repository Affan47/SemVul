smime_to_pkcs7 (void)
{
  size_t linesize = 0;
  char *lineptr = NULL;
  ssize_t len;


  do
    {
      len = getline (&lineptr, &linesize, infile);
      if (len == -1)
        error (EXIT_FAILURE, 0, "cannot find RFC 2822 header/body separator");
    }
  while (strcmp (lineptr, "\r\n") != 0 && strcmp (lineptr, "\n") != 0);

  do
    {
      len = getline (&lineptr, &linesize, infile);
      if (len == -1)
        error (EXIT_FAILURE, 0, "message has RFC 2822 header but no body");
    }
  while (strcmp (lineptr, "\r\n") == 0 && strcmp (lineptr, "\n") == 0);

  fprintf (outfile, "%s", "-----BEGIN PKCS7-----\n");

  do
    {
      while (len > 0
             && (lineptr[len - 1] == '\r' || lineptr[len - 1] == '\n'))
        lineptr[--len] = '\0';
      if (strcmp (lineptr, "") != 0)
        fprintf (outfile, "%s\n", lineptr);
      len = getline (&lineptr, &linesize, infile);
    }
  while (len != -1);

  fprintf (outfile, "%s", "-----END PKCS7-----\n");

  free (lineptr);
}
