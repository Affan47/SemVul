find_viewer(Display *display, Window window)
{
  Gt_Viewer *v;
  for (v = viewers; v; v = v->next)
    if (v->display == display && v->window == window)
      return v;
  return 0;
}
