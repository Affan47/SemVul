xscreensaver_command (Display *dpy, Atom command, long arg, Bool verbose_p,
                      char **error_ret)
{
  Window w = 0;
  int status = send_xscreensaver_command (dpy, command, arg, &w, error_ret);
  if (status == 0)
    status = xscreensaver_command_response (dpy, w, verbose_p,
                                            (command == XA_EXIT),
                                            error_ret);

  fflush (stdout);
  fflush (stderr);
  return (status < 0 ? status : 0);
}
