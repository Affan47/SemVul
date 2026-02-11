set_file_fd (const char *name, int fd)
{
  FILE *fp;
  int want_socket;
#ifdef USE_FUNWRITER
  struct fun_cookie_s *cookie;
#endif


  if (logstream)
    {
      if (logstream != stderr && logstream != stdout)
        fclose (logstream);
      logstream = NULL;
    }


  if (name && !strcmp (name, "-"))
    {
      name = NULL;
      fd = fileno (stderr);
    }

  if (name)
    {
      want_socket = (!strncmp (name, "socket://", 9) && name[9]);
      if (want_socket)
        name += 9;
    }
  else
    {
      want_socket = 0;
    }


#ifdef USE_FUNWRITER


  cookie = jnlib_xmalloc (sizeof *cookie + (name? strlen (name):0));
  strcpy (cookie->name, name? name:"");
  cookie->quiet = 0;
  cookie->is_socket = 0;
  cookie->want_socket = want_socket;
  if (!name)
    cookie->fd = fd;
  else if (want_socket)
    cookie->fd = -1;
  else
    {
      do
        cookie->fd = open (name, O_WRONLY|O_APPEND|O_CREAT,
                           (S_IRUSR|S_IRGRP|S_IROTH|S_IWUSR|S_IWGRP|S_IWOTH));
      while (cookie->fd == -1 && errno == EINTR);
    }
  log_socket = cookie->fd;

#ifdef HAVE_FOPENCOOKIE
  {
    cookie_io_functions_t io = { NULL };
    io.write = fun_writer;
    io.close = fun_closer;

    fp = fopencookie (cookie, "w", io);
  }
#else
  fp = funopen (cookie, NULL, fun_writer, NULL, fun_closer);
#endif

#else


  if (want_socket)
    {
      fprintf (stderr, "system does not support logging to a socket - "
               "using stderr\n");
      fp = stderr;
    }
  else if (name)
    fp = fopen (name, "a");
  else if (fd == 1)
    fp = stdout;
  else if (fd == 2)
    fp = stderr;
  else
    fp = fdopen (fd, "a");

  log_socket = -1;

#endif


  if (!fp)
    {
      if (name)
        fprintf (stderr, "failed to open log file `%s': %s\n",
                 name, strerror(errno));
      else
        fprintf (stderr, "failed to fdopen file descriptor %d: %s\n",
                 fd, strerror(errno));

      fp = stderr;
    }
  else
    setvbuf (fp, NULL, _IOLBF, 0);

  logstream = fp;


  force_prefixes = want_socket;

  missing_lf = 0;
}
