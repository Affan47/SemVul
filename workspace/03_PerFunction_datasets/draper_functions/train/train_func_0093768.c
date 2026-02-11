pick_visual (Screen *screen)
{
  struct xscreensaver_function_table *ft = xscreensaver_function_table;

  if (ft->pick_visual_hook)
    {
      Visual *v = ft->pick_visual_hook (screen);
      if (v) return v;
    }

  return get_visual_resource (screen, "visualID", "VisualID", False);
}
