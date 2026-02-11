do_debug_upload (const char *filename, int mode)
{


  int fd = open (filename, O_WRONLY|O_CREAT|O_TRUNC|O_NOCTTY|O_CLOEXEC, mode);

  if (fd == -1) {
    int err = errno;
    cancel_receive ();
    errno = err;
    reply_with_perror ("%s", filename);
    return -1;
  }

  int r = receive_file (write_cb, &fd);
  if (r == -1) {
    int err = errno;
    cancel_receive ();
    errno = err;
    reply_with_error ("write error: %s", filename);
    close (fd);
    return -1;
  }
  if (r == -2) {


    reply_with_error ("file upload cancelled");
    close (fd);
    return -1;
  }

  if (close (fd) == -1) {
    reply_with_perror ("close: %s", filename);
    return -1;
  }

  return 0;
}
