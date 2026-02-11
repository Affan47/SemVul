readln (char **out)
{
  if (sockfd)
    {
      size_t allocated = 0, used = 0;
      char *input = NULL;


      do
	{
	  ssize_t nread;

	  if (used == allocated)
	    input = x2realloc (input, &allocated);

#ifdef HAVE_LIBGNUTLS
	  if (using_tls)
	    nread = gnutls_record_recv (session, &input[used], 1);
	  else
#endif
	    nread = recv (sockfd, &input[used], 1, 0);
	  if (nread <= 0)
	    return 0;

	  used += nread;
	}
      while (input[used - 1] != '\n');

      if (used == allocated)
	input = x2realloc (input, &allocated);

      input[used] = '\0';

      *out = input;

      printf ("%s", *out);
    }
  else
    {
      *out = readline ("");
      if (*out == NULL)
	return 0;
    }

  return 1;
}
