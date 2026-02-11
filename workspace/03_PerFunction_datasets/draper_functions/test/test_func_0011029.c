do_base64_in (const char *file)
{
  int err, r;
  FILE *fp;
  CLEANUP_FREE char *cmd = NULL;

  if (asprintf_nowarn (&cmd, "%s -d -i > %R", str_base64, file) == -1) {
    err = errno;
    cancel_receive ();
    errno = err;
    reply_with_perror ("asprintf");
    return -1;
  }

  if (verbose)
    fprintf (stderr, "%s\n", cmd);

  fp = popen (cmd, "w");
  if (fp == NULL) {
    err = errno;
    cancel_receive ();
    errno = err;
    reply_with_perror ("%s", cmd);
    return -1;
  }


  int fd = fileno (fp);

  r = receive_file (write_cb, &fd);
  if (r == -1) {
    cancel_receive ();
    reply_with_error ("write error on file: %s", file);
    pclose (fp);
    return -1;
  }
  if (r == -2) {


    reply_with_error ("file upload cancelled");
    pclose (fp);
    return -1;
  }

  if (pclose (fp) != 0) {
    reply_with_error ("base64 subcommand failed on file: %s", file);
    return -1;
  }

  return 0;
}
