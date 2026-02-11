get_resources(struct state *st)

{
  Bool rise;
  XWindowAttributes xgwa;
  Colormap cmap;
  char *s;
  XGetWindowAttributes (st->dpy, st->window, &xgwa);
  cmap = xgwa.colormap;

  st->threed = get_boolean_resource(st->dpy, "3D", "Boolean");
  st->quiet = get_boolean_resource(st->dpy, "quiet", "Boolean");
  st->simple = get_boolean_resource(st->dpy, "simple", "Boolean");

  if ((mono_p) && (! st->simple)) {
    if (! st->quiet)
      fprintf(stderr,
	      "Rendered bubbles not supported on monochrome displays\n");
    st->simple = True;
  }
  st->delay = get_integer_resource(st->dpy, "delay", "Integer");

  s = get_string_resource (st->dpy, "mode", "Mode");
  rise = False;
  if (!s || !*s || !strcasecmp (s, "float"))
    ;
  else if (!strcasecmp (s, "rise"))
    rise = True;
  else if (!strcasecmp (s, "drop"))
    st->drop = True;
  else
    fprintf (stderr, "%s: bogus mode: \"%s\"\n", progname, s);

  st->trails = get_boolean_resource(st->dpy, "trails", "Boolean");
  st->drop_dir = (st->drop ? 1 : -1);
  if (st->drop || rise)
	st->drop = 1;

  st->default_fg_pixel = get_pixel_resource (st->dpy,
					 cmap, "foreground", "Foreground");
  st->default_bg_pixel = get_pixel_resource (st->dpy,
					 cmap, "background", "Background");

  if (st->simple) {

    st->broken = get_boolean_resource(st->dpy, "broken", "Boolean");
    if (st->broken)
      if (! st->quiet)
	fprintf(stderr, "-broken not available in simple mode\n");
  } else {
#ifndef FANCY_BUBBLES
    st->simple = 1;
#else
    st->broken = get_boolean_resource(st->dpy, "broken", "Boolean");
#endif
  }
}
