XGetAtomName_safe (Display *dpy, Atom atom)
{
  char *result;
  XErrorHandler old_handler;
  if (!atom) return 0;

  XSync (dpy, False);
  error_handler_hit_p = False;
  old_handler = XSetErrorHandler (ignore_all_errors_ehandler);
  result = XGetAtomName (dpy, atom);
  XSync (dpy, False);
  XSetErrorHandler (old_handler);
  XSync (dpy, False);
  if (error_handler_hit_p) result = 0;

  if (result)
    return result;
  else
    {
      char buf[100];
      sprintf (buf, "<<undefined atom 0x%04X>>", (unsigned int) atom);
      return strdup (buf);
    }
}
