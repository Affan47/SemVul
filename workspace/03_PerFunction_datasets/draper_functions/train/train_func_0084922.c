gftp_find_cache_entry (gftp_request * request)
{
  char *indexfile, buf[BUFSIZ], description[BUFSIZ];
  gftp_getline_buffer * rbuf;
  gftp_cache_entry centry;
  int indexfd, cachefd;
  time_t now;

  time (&now);

  *description = '\0';
  gftp_generate_cache_description (request, description, sizeof (description),
                                   0);

  indexfile = gftp_expand_path (NULL, BASE_CONF_DIR "/cache/index.db");
  if ((indexfd = gftp_fd_open (NULL, indexfile, O_RDONLY, 0)) == -1)
    {
      g_free (indexfile);
      return (-1);
    }
  g_free (indexfile);

  rbuf = NULL;
  while (gftp_get_line (NULL, &rbuf, buf, sizeof (buf), indexfd) > 0)
    {
      if (gftp_parse_cache_line (request, &centry, buf) < 0)
        continue;


      if (centry.expiration_date < now)
        continue;

      if (strcmp (description, centry.url) == 0)
	{
	  if (close (indexfd) != 0)
            {
              if (request != NULL)
                request->logging_function (gftp_logging_error, request,
                                       _("Error closing file descriptor: %s\n"),
                                       g_strerror (errno));
              return (-1);
            }

	  if ((cachefd = gftp_fd_open (request, centry.file, O_RDONLY, 0)) == -1)
            return (-1);

          if (lseek (cachefd, 0, SEEK_END) == 0)
            {
              close (cachefd);
              return (-1);
            }

          if (lseek (cachefd, 0, SEEK_SET) == -1)
            {
              if (request != NULL)
                request->logging_function (gftp_logging_error, request,
                                       _("Error: Cannot seek on file %s: %s\n"),
                                       centry.file, g_strerror (errno));

            }

          request->server_type = centry.server_type;
	  return (cachefd);
	}
    }
  close (indexfd);
  return (-1);
}
