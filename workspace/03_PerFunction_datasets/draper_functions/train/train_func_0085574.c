critical_init (Display *dpy, Window window)
{
  struct state *st = (struct state *) calloc (1, sizeof(*st));
  int			model_w, model_h;
  st->dpy = dpy;
  st->window = window;


  XGetWindowAttributes (st->dpy, st->window, &st->wattr);

  st->batchcount = get_integer_resource (st->dpy, "batchcount", "Integer");
  if (st->batchcount < 5)
    st->batchcount = 5;

  st->lines_per_color = 10;


  model_w = 80;
  st->settings.cell_size = st->wattr.width / model_w;
  model_h = st->settings.cell_size ?
    st->wattr.height / st->settings.cell_size : 0;


  st->settings.trail = clip(2, get_integer_resource (st->dpy, "trail", "Integer"), 1000);

  st->history = calloc (st->settings.trail, sizeof (st->history[0]));
  if (!st->history)
    {
      fprintf (stderr, "critical: "
	       "couldn't allocate trail history of %d cells\n",
	       st->settings.trail);
      abort();
    }

  st->model = model_allocate (model_w, model_h);
  if (!st->model)
    {
      fprintf (stderr, "critical: error preparing the model\n");
      abort();
    }


  st->gcv.foreground = get_pixel_resource (st->dpy, st->wattr.colormap,
                                       "background", "Background");
  st->bgc = XCreateGC (st->dpy, st->window, GCForeground, &st->gcv);

  st->fgc = XCreateGC (st->dpy, st->window, 0, &st->gcv);

#ifdef HAVE_COCOA
  jwxyz_XSetAntiAliasing (dpy, st->fgc, False);
  jwxyz_XSetAntiAliasing (dpy, st->bgc, False);
#endif

  st->delay_usecs = get_integer_resource (st->dpy, "delay", "Integer");
  st->n_restart = get_integer_resource (st->dpy, "restart", "Integer");

  setup_colormap (st, &st->d_colors, &st->d_n_colors);
  model_initialize (st->model);
  model_step (st->model, &st->history[0]);
  st->d_pos = 1;
  st->d_wrapped = 0;
  st->i_restart = 0;
  st->d_i_batch = st->batchcount;

  return st;
}
