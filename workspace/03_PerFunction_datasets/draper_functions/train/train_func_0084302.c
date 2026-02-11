visual_warning (Screen *screen, Window window, Visual *visual, Colormap cmap,
                Bool window_p)
{
  struct xscreensaver_function_table *ft = xscreensaver_function_table;

  char *visual_string = get_string_resource (DisplayOfScreen (screen),
                                             "visualID", "VisualID");
  Visual *desired_visual = pick_visual (screen);
  char win[100];
  char why[100];

  if (window == RootWindowOfScreen (screen))
    strcpy (win, "root window");
  else
    sprintf (win, "window 0x%lx", (unsigned long) window);

  if (window_p)
    sprintf (why, "-window-id 0x%lx", (unsigned long) window);
  else
    strcpy (why, "-root");

  if (visual_string && *visual_string)
    {
      char *s;
      for (s = visual_string; *s; s++)
        if (isupper (*s)) *s = _tolower (*s);

      if (!strcmp (visual_string, "default") ||
          !strcmp (visual_string, "default") ||
          !strcmp (visual_string, "best"))

        ;
      else if (visual != desired_visual)
        {
          fprintf (stderr, "%s: ignoring `-visual %s' because of `%s'.\n",
                   progname, visual_string, why);
          fprintf (stderr, "%s: using %s's visual 0x%lx.\n",
                   progname, win, XVisualIDFromVisual (visual));
        }
      free (visual_string);
    }

  if (visual == DefaultVisualOfScreen (screen) &&
      has_writable_cells (screen, visual) &&
      get_boolean_resource (DisplayOfScreen (screen),
                            "installColormap", "InstallColormap"))
    {
      fprintf (stderr, "%s: ignoring `-install' because of `%s'.\n",
               progname, why);
      fprintf (stderr, "%s: using %s's colormap 0x%lx.\n",
               progname, win, (unsigned long) cmap);
    }

  if (ft->validate_visual_hook)
    {
      if (! ft->validate_visual_hook (screen, win, visual))
        exit (1);
    }
}
