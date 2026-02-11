set_bgcolor (struct cmdarg **args)
{
  int i;
  XColor color, junk;

  if (args[0] == NULL)
    return cmdret_new (RET_SUCCESS, "%s", defaults.bgcolor_string);

  for (i=0; i<num_screens; i++)
    {
      if (!XAllocNamedColor (dpy, screens[i].def_cmap, ARG_STRING(0), &color, &junk))
        return cmdret_new (RET_FAILURE, "defbgcolor: unknown color");

      screens[i].bg_color = color.pixel;
      update_gc (&screens[i]);
      XSetWindowBackground (dpy, screens[i].bar_window, color.pixel);
      XSetWindowBackground (dpy, screens[i].input_window, color.pixel);
      XSetWindowBackground (dpy, screens[i].frame_window, color.pixel);
      XSetWindowBackground (dpy, screens[i].help_window, color.pixel);

#ifdef USE_XFT_FONT
      if (!XftColorAllocName (dpy, DefaultVisual (dpy, screens[i].screen_num),
                              DefaultColormap (dpy, screens[i].screen_num),
                              ARG_STRING(0), &screens[i].xft_bg_color))
        return cmdret_new (RET_FAILURE, "deffgcolor: unknown color");
#endif

      free (defaults.bgcolor_string);
      defaults.bgcolor_string = xstrdup (ARG_STRING(0));
    }

  return cmdret_new (RET_SUCCESS, NULL);
}
